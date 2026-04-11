import pygame
import random
import heapq
import time
import threading
from collections import deque
import sys

# Grid parameters
ROWS, COLS  = 25, 25
TOTAL_CELLS = ROWS * COLS
NUM_BLOCKED = round(TOTAL_CELLS * 0.30)

# Minimum window dimensions
MIN_SCREEN_W = 636 + 396 + 32   # grid + panel + margins
MIN_SCREEN_H = 620

# Colours
BG          = (15,  15,  26)
PANEL_BG    = (18,  24,  48)
GRID_LINE   = (50,  50,  70)
C_FREE      = (255, 255, 255)
C_BLOCKED   = (26,  26,  46)
C_START     = (0,   200, 83)
C_GOAL      = (255, 214, 0)
C_AGENT     = (41,  121, 255)
C_PATH      = (0,   230, 118)
C_ACCENT    = (233, 69,  96)
C_TEXT      = (220, 220, 220)
C_SUBTEXT   = (225, 225, 235)
C_GOLD      = (255, 214, 0)
C_GREEN     = (0,   230, 118)
C_DARK_BTN  = (15,  52,  96)
C_HOVER_BTN = (233, 69,  96)

VISIT_COLS = {
    1: (255, 138, 128),
    2: (255,  82,  82),
    3: (255,  23,  68),
    4: (213,   0,   0),
}
VISIT_5PLUS = (139, 0, 0)


class Grid:
    def __init__(self):
        self.blocked     = [[False] * COLS for _ in range(ROWS)]
        self.visit_count = [[0]     * COLS for _ in range(ROWS)]
        self.start = (0, 0)
        self.goal  = (ROWS - 1, COLS - 1)
        self.agent = self.start

    def clearObstacles(self):
        self.blocked = [[False] * COLS for _ in range(ROWS)]

    def generateObstacles(self):
        protected  = {self.start, self.goal, self.agent}
        candidates = [(r, c) for r in range(ROWS) for c in range(COLS)
                      if (r, c) not in protected]
        chosen = random.sample(candidates, min(NUM_BLOCKED, len(candidates)))
        for r, c in chosen:
            self.blocked[r][c] = True

    def resetObstacles(self):
        attempts = 0
        while True:
            self.clearObstacles()
            self.generateObstacles()
            if self.isReachable(self.agent, self.goal):
                break
            attempts += 1
            if attempts > 300:
                break

    def isReachable(self, src, dst):
        if src == dst:
            return True
        visited = {src}
        queue   = deque([src])
        while queue:
            r, c = queue.popleft()
            for nr, nc in self.getNeighbors(r, c):
                if (nr, nc) == dst:
                    return True
                if (nr, nc) not in visited:
                    visited.add((nr, nc))
                    queue.append((nr, nc))
        return False

    def getNeighbors(self, r, c):
        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nr, nc = r + dr, c + dc
            if 0 <= nr < ROWS and 0 <= nc < COLS and not self.blocked[nr][nc]:
                yield nr, nc

    def recordVisit(self, pos):
        r, c = pos
        self.visit_count[r][c] += 1

    def getCellColour(self, r, c, agent, start, goal, pathSet):
        pos = (r, c)
        if pos == agent:        return C_AGENT
        if pos == start:        return C_START
        if pos == goal:         return C_GOAL
        if pos in pathSet:      return C_PATH
        if self.blocked[r][c]:  return C_BLOCKED
        v = self.visit_count[r][c]
        if v == 0:  return C_FREE
        if v >= 5:  return VISIT_5PLUS
        return VISIT_COLS.get(v, VISIT_5PLUS)


# Search algorithms

def getManhattanDistance(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def getNovelHeuristic(grid, a, b):
    base    = getManhattanDistance(a, b)
    r0, c0  = min(a[0], b[0]), min(a[1], b[1])
    r1, c1  = max(a[0], b[0]), max(a[1], b[1])
    total   = max(1, (r1 - r0 + 1) * (c1 - c0 + 1))
    blocked = sum(1 for r in range(r0, r1 + 1)
                    for c in range(c0, c1 + 1)
                    if grid.blocked[r][c])
    density = blocked / total
    return base + 0.5 * density * base


HEURISTIC_USE_NOVEL = False

def getHeuristic(grid, a, b):
    if HEURISTIC_USE_NOVEL:
        return getNovelHeuristic(grid, a, b)
    return getManhattanDistance(a, b)

HEURISTIC_NAMES = ["Manhattan", "Novel (Density)"]


def runDFS(grid, start, goal):
    stack = [(start, [start])]
    visited = {start}
    while stack:
        (r, c), path = stack.pop()
        if (r, c) == goal:
            return path[1] if len(path) > 1 else goal
        for nr, nc in grid.getNeighbors(r, c):
            if (nr, nc) not in visited:
                visited.add((nr, nc))
                stack.append(((nr, nc), path + [(nr, nc)]))
    return None


def runBFS(grid, start, goal):
    queue = deque([(start, [start])])
    visited = {start}
    while queue:
        (r, c), path = queue.popleft()
        if (r, c) == goal:
            return path[1] if len(path) > 1 else goal
        for nr, nc in grid.getNeighbors(r, c):
            if (nr, nc) not in visited:
                visited.add((nr, nc))
                queue.append(((nr, nc), path + [(nr, nc)]))
    return None


def runUCS(grid, start, goal):
    pq = [(0, start, [start])]
    visited = {}
    while pq:
        cost, (r, c), path = heapq.heappop(pq)
        if (r, c) == goal:
            return path[1] if len(path) > 1 else goal
        if (r, c) in visited and visited[(r, c)] <= cost:
            continue
        visited[(r, c)] = cost
        for nr, nc in grid.getNeighbors(r, c):
            newCost = cost + 1
            if (nr, nc) not in visited or visited[(nr, nc)] > newCost:
                heapq.heappush(pq, (newCost, (nr, nc), path + [(nr, nc)]))
    return None


def runGreedy(grid, start, goal):
    pq = [(getHeuristic(grid, start, goal), start, [start])]
    visited = {start}
    while pq:
        _, (r, c), path = heapq.heappop(pq)
        if (r, c) == goal:
            return path[1] if len(path) > 1 else goal
        for nr, nc in grid.getNeighbors(r, c):
            if (nr, nc) not in visited:
                visited.add((nr, nc))
                h = getHeuristic(grid, (nr, nc), goal)
                heapq.heappush(pq, (h, (nr, nc), path + [(nr, nc)]))
    return None


def runAStar(grid, start, goal):
    pq = [(getHeuristic(grid, start, goal), 0, start, [start])]
    visited = {}
    while pq:
        f, g, (r, c), path = heapq.heappop(pq)
        if (r, c) == goal:
            return path[1] if len(path) > 1 else goal
        if (r, c) in visited and visited[(r, c)] <= g:
            continue
        visited[(r, c)] = g
        for nr, nc in grid.getNeighbors(r, c):
            ng = g + 1
            if (nr, nc) not in visited or visited[(nr, nc)] > ng:
                nf = ng + getHeuristic(grid, (nr, nc), goal)
                heapq.heappush(pq, (nf, ng, (nr, nc), path + [(nr, nc)]))
    return None


def computeOptimalPath(grid, start, goal):
    pq = [(getManhattanDistance(start, goal), 0, start, [start])]
    visited = {}
    while pq:
        f, g, (r, c), path = heapq.heappop(pq)
        if (r, c) == goal:
            return path
        if (r, c) in visited and visited[(r, c)] <= g:
            continue
        visited[(r, c)] = g
        for nr, nc in grid.getNeighbors(r, c):
            ng = g + 1
            if (nr, nc) not in visited or visited[(nr, nc)] > ng:
                nf = ng + getManhattanDistance((nr, nc), goal)
                heapq.heappush(pq, (nf, ng, (nr, nc), path + [(nr, nc)]))
    return []


ALGORITHMS = {
    "DFS":     runDFS,
    "BFS":     runBFS,
    "UCS":     runUCS,
    "Best-FS": runGreedy,
    "A*":      runAStar,
}
ALGO_NAMES = list(ALGORITHMS.keys())
HEURISTIC_ALGOS = {"Best-FS", "A*"}


# UI Widgets

class Button:
    def __init__(self, rect, label, enabled=True):
        self.rect    = pygame.Rect(rect)
        self.label   = label
        self.enabled = enabled
        self._hover  = False

    def draw(self, surf, font):
        col = C_HOVER_BTN if (self._hover and self.enabled) else C_DARK_BTN
        if not self.enabled:
            col = (30, 30, 50)
        pygame.draw.rect(surf, col, self.rect, border_radius=5)
        pygame.draw.rect(surf, C_ACCENT, self.rect, 1, border_radius=5)
        tc  = C_TEXT if self.enabled else C_SUBTEXT
        txt = font.render(self.label, True, tc)
        surf.blit(txt, txt.get_rect(center=self.rect.center))

    def handleEvent(self, event):
        if event.type == pygame.MOUSEMOTION:
            self._hover = self.rect.collidepoint(event.pos)
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            if self.enabled and self.rect.collidepoint(event.pos):
                return True
        return False

    def reposition(self, rect):
        self.rect = pygame.Rect(rect)


class Dropdown:
    def __init__(self, rect, options, selected=0):
        self.rect      = pygame.Rect(rect)
        self.options   = options
        self.selected  = selected
        self.open      = False
        self.enabled   = True
        self._hoverIdx = -1

    @property
    def value(self):
        return self.options[self.selected]

    def draw(self, surf, font):
        col = C_DARK_BTN if self.enabled else (30, 30, 50)
        pygame.draw.rect(surf, col, self.rect, border_radius=4)
        pygame.draw.rect(surf, C_GOLD, self.rect, 1, border_radius=4)
        tc  = C_GOLD if self.enabled else C_SUBTEXT
        txt = font.render(self.options[self.selected], True, tc)
        surf.blit(txt, (self.rect.x + 8, self.rect.centery - txt.get_height() // 2))
        arrow = font.render("v", True, C_GOLD)
        surf.blit(arrow, (self.rect.right - 20, self.rect.centery - arrow.get_height() // 2))
        if self.open:
            ih = self.rect.height
            for i, opt in enumerate(self.options):
                r = pygame.Rect(self.rect.x, self.rect.bottom + i * ih, self.rect.w, ih)
                bg = C_ACCENT if i == self._hoverIdx else (30, 40, 70)
                pygame.draw.rect(surf, bg, r)
                pygame.draw.rect(surf, C_GOLD, r, 1)
                ot = font.render(opt, True, C_TEXT)
                surf.blit(ot, (r.x + 8, r.centery - ot.get_height() // 2))

    def handleEvent(self, event):
        if not self.enabled:
            return False
        ih = self.rect.height
        if event.type == pygame.MOUSEMOTION:
            self._hoverIdx = -1
            if self.open:
                for i in range(len(self.options)):
                    r = pygame.Rect(self.rect.x, self.rect.bottom + i * ih, self.rect.w, ih)
                    if r.collidepoint(event.pos):
                        self._hoverIdx = i
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            if self.rect.collidepoint(event.pos):
                self.open = not self.open
                return False
            if self.open:
                for i in range(len(self.options)):
                    r = pygame.Rect(self.rect.x, self.rect.bottom + i * ih, self.rect.w, ih)
                    if r.collidepoint(event.pos):
                        self.selected  = i
                        self.open      = False
                        return True
                self.open = False
        return False

    def reposition(self, rect):
        self.rect = pygame.Rect(rect)


class Slider:
    def __init__(self, rect, minVal, maxVal, value):
        self.rect   = pygame.Rect(rect)
        self.minVal = minVal
        self.maxVal = maxVal
        self.value  = value
        self._drag  = False

    def draw(self, surf, font):
        cy = self.rect.centery
        pygame.draw.line(surf, C_DARK_BTN, (self.rect.x, cy), (self.rect.right, cy), 4)
        ratio = (self.value - self.minVal) / (self.maxVal - self.minVal)
        kx    = int(self.rect.x + ratio * self.rect.width)
        pygame.draw.circle(surf, C_ACCENT, (kx, cy), 8)
        pygame.draw.circle(surf, C_TEXT,   (kx, cy), 8, 2)
        lbl = font.render(f"{self.value} ms", True, C_SUBTEXT)
        surf.blit(lbl, (self.rect.right - lbl.get_width(), self.rect.y - 16))

    def handleEvent(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            if self.rect.inflate(0, 20).collidepoint(event.pos):
                self._drag = True
        if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
            self._drag = False
        if event.type == pygame.MOUSEMOTION and self._drag:
            ratio      = (event.pos[0] - self.rect.x) / max(self.rect.width, 1)
            ratio      = max(0.0, min(1.0, ratio))
            self.value = int(self.minVal + ratio * (self.maxVal - self.minVal))
            self.value = (self.value // 10) * 10

    def reposition(self, rect):
        self.rect = pygame.Rect(rect)


class TextInput:
    def __init__(self, rect, default=""):
        self.rect   = pygame.Rect(rect)
        self.text   = str(default)
        self.active = False

    def draw(self, surf, font):
        col = C_ACCENT if self.active else C_DARK_BTN
        pygame.draw.rect(surf, C_DARK_BTN, self.rect, border_radius=3)
        pygame.draw.rect(surf, col,        self.rect, 1, border_radius=3)
        txt = font.render(self.text, True, C_GOLD)
        surf.blit(txt, (self.rect.x + 4, self.rect.centery - txt.get_height() // 2))

    def handleEvent(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            self.active = self.rect.collidepoint(event.pos)
        if event.type == pygame.KEYDOWN and self.active:
            if event.key == pygame.K_BACKSPACE:
                self.text = self.text[:-1]
            elif event.unicode.isdigit() and len(self.text) < 2:
                self.text += event.unicode

    def getInt(self, default=0):
        try:
            return int(self.text)
        except ValueError:
            return default

    def reposition(self, rect):
        self.rect = pygame.Rect(rect)


# Main application

class App:
    def __init__(self):
        pygame.init()

        # Detect monitor size and default to full screen
        info        = pygame.display.Info()
        initW       = max(info.current_w,  MIN_SCREEN_W)
        initH       = max(info.current_h,  MIN_SCREEN_H)
        self.screen = pygame.display.set_mode(
            (initW, initH),
            pygame.RESIZABLE
        )
        pygame.display.set_caption("AI Path-Finding Agent - COEP Lab 1")
        self.clock  = pygame.time.Clock()

        self.screenW = initW
        self.screenH = initH

        self.fontHd = pygame.font.SysFont("monospace", 22, bold=True)
        self.fontLg = pygame.font.SysFont("monospace", 19, bold=True)
        self.fontMd = pygame.font.SysFont("monospace", 17)
        self.fontSm = pygame.font.SysFont("monospace", 15)

        # Simulation state
        self.gridModel   = Grid()
        self.runningSim  = False
        self.paused      = False
        self.simThread   = None
        self.stepCount   = 0
        self.uniqueCells = set()
        self.optimalPath = []
        self.pathSet     = set()
        self.statusMsg   = "Ready - set Start & Goal, then press START"
        self.clickPhase  = 0    # 0=set start, 1=set goal, 2=done
        self._lock       = threading.Lock()

        # Widgets
        self.dropdown    = Dropdown((0, 0, 10, 10), ALGO_NAMES, selected=4)
        self.ddHeuristic = Dropdown((0, 0, 10, 10), HEURISTIC_NAMES, selected=0)
        self.inpSr    = TextInput((0, 0, 10, 10), "0")
        self.inpSc    = TextInput((0, 0, 10, 10), "0")
        self.inpGr    = TextInput((0, 0, 10, 10), "24")
        self.inpGc    = TextInput((0, 0, 10, 10), "24")
        self.btnStart = Button((0, 0, 10, 10), "START")
        self.btnPause = Button((0, 0, 10, 10), "PAUSE", enabled=False)
        self.btnReset = Button((0, 0, 10, 10), "RESET")
        self.slider   = Slider((0, 0, 10, 10), 50, 1000, 250)

        self.stat = {
            "Algorithm":    "-",
            "Steps":        "-",
            "Unique cells": "-",
            "Optimal path": "-",
        }

        # Compute initial layout
        self.updateLayout()

    #Layout
    
    # Returns a dict of all layout values derived from current screen size
    def computeLayout(self):
        sw, sh = self.screenW, self.screenH

        # Grid: fill available height, keep cells square
        gridMargin = 10
        availH     = sh - gridMargin * 2
        availW     = sw - gridMargin * 2
        # Panel takes a fixed proportion of width (min 380px)
        panelW     = max(380, int(sw * 0.37))
        gridAreaW  = sw - panelW - gridMargin * 3
        cellSize   = max(12, min(availH // ROWS, gridAreaW // COLS))
        gridW      = COLS * cellSize
        gridH      = ROWS * cellSize
        gridOx     = gridMargin
        gridOy     = max(gridMargin, (sh - gridH) // 2)

        panelX     = gridOx + gridW + gridMargin
        panelInner = panelX + 14      # inner left edge of panel content
        panelRW    = panelW - 28      # usable row width inside panel

        return dict(
            cellSize=cellSize, gridW=gridW, gridH=gridH,
            gridOx=gridOx, gridOy=gridOy,
            panelX=panelX, panelW=panelW,
            panelInner=panelInner, panelRW=panelRW,
        )

	# Reposition all widgets based on current screen size
    def updateLayout(self):
        L  = self.computeLayout()
        px = L["panelInner"]
        rw = L["panelRW"]

        self.dropdown.reposition((px, 74, rw, 34))

        useHeuristic = self.dropdown.value in HEURISTIC_ALGOS
        self.ddHeuristic.reposition((px, 118, rw, 34))

        coordY = 162 if useHeuristic else 118
        iw = 44
        self.inpSr.reposition((px + 170, coordY,      iw, 26))
        self.inpSc.reposition((px + 222, coordY,      iw, 26))
        self.inpGr.reposition((px + 170, coordY + 32, iw, 26))
        self.inpGc.reposition((px + 222, coordY + 32, iw, 26))

        buttonY = coordY + 88
        bw = rw // 2 - 5
        self.btnStart.reposition((px,           buttonY,      bw, 36))
        self.btnPause.reposition((px + bw + 10, buttonY,      bw, 36))
        self.btnReset.reposition((px,           buttonY + 44, rw, 36))
        self.slider.reposition(  (px,           buttonY + 124, rw, 18))

        self._layout = L

    def run(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.runningSim = False
                    pygame.quit()
                    sys.exit()
                self.handleEvent(event)

            w, h = self.screen.get_size()

            if w < MIN_SCREEN_W or h < MIN_SCREEN_H:
                w = max(w, MIN_SCREEN_W)
                h = max(h, MIN_SCREEN_H)
                self.screen = pygame.display.set_mode((w, h), pygame.RESIZABLE)
            if w != self.screenW or h != self.screenH:
                self.screenW = w
                self.screenH = h
                self.updateLayout()

            self.screen.fill(BG)
            self.drawGrid()
            self.drawPanel()
            pygame.display.flip()
            self.clock.tick(60)

    # Event handling
    def handleEvent(self, event):
        global HEURISTIC_USE_NOVEL
        L = self._layout
        gridOx, gridOy = L["gridOx"], L["gridOy"]
        gridW,  gridH  = L["gridW"],  L["gridH"]
        cell           = L["cellSize"]

        # Grid click to set start / goal
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            mx, my = event.pos
            if (gridOx <= mx < gridOx + gridW and
                    gridOy <= my < gridOy + gridH and
                    not self.runningSim and
                    not self.dropdown.open and
                    not self.ddHeuristic.open):
                c = (mx - gridOx) // cell
                r = (my - gridOy) // cell
                if 0 <= r < ROWS and 0 <= c < COLS:
                    self.handleGridClick(r, c)

        # Dropdown gets priority when open
        if self.dropdown.open:
            self.dropdown.handleEvent(event)
            if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                ih          = self.dropdown.rect.height
                dropRegion  = pygame.Rect(
                    self.dropdown.rect.x,
                    self.dropdown.rect.bottom,
                    self.dropdown.rect.w,
                    ih * len(ALGO_NAMES)
                )
                if dropRegion.collidepoint(event.pos) or \
                        self.dropdown.rect.collidepoint(event.pos):
                    return
            return

        if self.ddHeuristic.open:
            changed = self.ddHeuristic.handleEvent(event)
            if changed:
                HEURISTIC_USE_NOVEL = (self.ddHeuristic.selected == 1)
            if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                ih         = self.ddHeuristic.rect.height
                dropRegion = pygame.Rect(
                    self.ddHeuristic.rect.x,
                    self.ddHeuristic.rect.bottom,
                    self.ddHeuristic.rect.w,
                    ih * len(HEURISTIC_NAMES)
                )
                if dropRegion.collidepoint(event.pos) or \
                        self.ddHeuristic.rect.collidepoint(event.pos):
                    return
            return

        if self.btnStart.handleEvent(event): self.startSim()
        if self.btnPause.handleEvent(event): self.togglePause()
        if self.btnReset.handleEvent(event): self.resetSim()
        if self.dropdown.handleEvent(event):
            self.updateLayout()
            if self.dropdown.value not in HEURISTIC_ALGOS:
                self.ddHeuristic.open = False
        if self.dropdown.value in HEURISTIC_ALGOS:
            changed = self.ddHeuristic.handleEvent(event)
            if changed:
                HEURISTIC_USE_NOVEL = (self.ddHeuristic.selected == 1)
        self.slider.handleEvent(event)
        for w in (self.inpSr, self.inpSc, self.inpGr, self.inpGc):
            w.handleEvent(event)

    def handleGridClick(self, r, c):
        if self.clickPhase == 0:
            self.gridModel.start = (r, c)
            self.gridModel.agent = (r, c)
            self.inpSr.text  = str(r)
            self.inpSc.text  = str(c)
            self.clickPhase  = 1
            self.statusMsg   = "Start set - now click Goal cell"
        elif self.clickPhase == 1:
            if (r, c) == self.gridModel.start:
                return
            self.gridModel.goal = (r, c)
            self.inpGr.text  = str(r)
            self.inpGc.text  = str(c)
            self.clickPhase  = 2
            self.statusMsg   = "Start & Goal set - press START"

    # Simulation controls
    def startSim(self):
        sr = self.inpSr.getInt(0);   sc = self.inpSc.getInt(0)
        gr = self.inpGr.getInt(24);  gc = self.inpGc.getInt(24)

        if not (0 <= sr < ROWS and 0 <= sc < COLS and
                0 <= gr < ROWS and 0 <= gc < COLS):
            self.statusMsg = "ERROR: coordinates must be 0-24"
            return
        if (sr, sc) == (gr, gc):
            self.statusMsg = "ERROR: Start and Goal must differ"
            return

        self.gridModel         = Grid()
        self.gridModel.start   = (sr, sc)
        self.gridModel.goal    = (gr, gc)
        self.gridModel.agent   = (sr, sc)
        self.gridModel.resetObstacles()
        self.gridModel.recordVisit((sr, sc))

        self.stepCount   = 0
        self.uniqueCells = {(sr, sc)}
        self.optimalPath = []
        self.pathSet     = set()
        self.runningSim  = True
        self.paused      = False
        self.clickPhase  = 0

        algo = self.dropdown.value
        self.stat["Algorithm"]    = algo
        self.stat["Steps"]        = "0"
        self.stat["Unique cells"] = "1"
        self.stat["Optimal path"] = "-"
        self.statusMsg = f"Algorithm: {algo} | Searching..."

        self.dropdown.enabled    = False
        self.ddHeuristic.enabled = False
        self.btnStart.enabled    = False
        self.btnPause.enabled  = True
        self.btnPause.label    = "PAUSE"

        self.simThread = threading.Thread(target=self.simLoop, daemon=True)
        self.simThread.start()

    def togglePause(self):
        if not self.runningSim:
            return
        self.paused          = not self.paused
        self.btnPause.label  = "RESUME" if self.paused else "PAUSE"
        self.statusMsg       = ("Paused." if self.paused
                                else f"Algorithm: {self.dropdown.value} | Searching...")

    def resetSim(self):
        self.runningSim = False
        self.paused     = False
        if self.simThread and self.simThread.is_alive():
            self.simThread.join(timeout=1.5)

        self.gridModel   = Grid()
        self.stepCount   = 0
        self.uniqueCells = set()
        self.optimalPath = []
        self.pathSet     = set()
        self.clickPhase  = 0
        self.statusMsg   = "Ready - set Start & Goal, then press START"

        self.dropdown.enabled    = True
        self.ddHeuristic.enabled = True
        self.btnStart.enabled    = True
        self.btnPause.enabled    = False
        self.btnPause.label      = "PAUSE"
        for k in self.stat:
            self.stat[k] = "-"

    # Simulation loop
    def simLoop(self):
        g      = self.gridModel
        algoFn = ALGORITHMS[self.dropdown.value]
        name   = self.dropdown.value

        while self.runningSim:
            while self.paused and self.runningSim:
                time.sleep(0.05)
            if not self.runningSim:
                break

            if g.agent == g.goal:
                self.finishSim()
                return

            nextCell = algoFn(g, g.agent, g.goal)

            if nextCell is None:
                self.statusMsg = "No path - re-randomising..."
                g.resetObstacles()
                time.sleep(self.slider.value / 1000)
                continue

            with self._lock:
                g.agent = nextCell
                self.stepCount += 1
                self.uniqueCells.add(nextCell)
                g.recordVisit(nextCell)

            self.stat["Steps"]        = str(self.stepCount)
            self.stat["Unique cells"] = str(len(self.uniqueCells))
            self.statusMsg = f"Algorithm: {name} | Step: {self.stepCount}"

            if g.agent == g.goal:
                self.finishSim()
                return

            g.resetObstacles()
            time.sleep(self.slider.value / 1000)

    def finishSim(self):
        g   = self.gridModel
        self.runningSim = False

        opt = computeOptimalPath(g, g.start, g.goal)
        with self._lock:
            self.optimalPath = opt
            self.pathSet     = set(opt)

        optLen = max(len(opt) - 1, 0)
        if optLen == 0:
            self.stat["Optimal path"] = "N/A"
        else:
            self.stat["Optimal path"] = f"{optLen} steps"
        self.statusMsg = (f"Goal reached in {self.stepCount} steps | "
                          f"Optimal: {optLen} steps")
        self.dropdown.enabled    = True
        self.ddHeuristic.enabled = True
        self.btnStart.enabled    = True
        self.btnPause.enabled    = False

    # Drawing
    def drawGrid(self):
        L    = self._layout
        cell = L["cellSize"]
        ox   = L["gridOx"]
        oy   = L["gridOy"]

        with self._lock:
            g     = self.gridModel
            agent = g.agent
            start = g.start
            goal  = g.goal
            ps    = self.pathSet

        for r in range(ROWS):
            for c in range(COLS):
                x   = ox + c * cell
                y   = oy + r * cell
                col = g.getCellColour(r, c, agent, start, goal, ps)
                pygame.draw.rect(self.screen, col, (x + 1, y + 1, cell - 2, cell - 2))
                pos = (r, c)
                if pos == start:
                    self.drawCellLabel(x, y, cell, "S", (0, 40, 0))
                elif pos == goal:
                    self.drawCellLabel(x, y, cell, "G", (80, 60, 0))
                elif pos == agent and pos not in (start, goal):
                    self.drawCellLabel(x, y, cell, "A", (200, 220, 255))

        for r in range(ROWS + 1):
            y = oy + r * cell
            pygame.draw.line(self.screen, GRID_LINE, (ox, y), (ox + L["gridW"], y))
        for c in range(COLS + 1):
            x = ox + c * cell
            pygame.draw.line(self.screen, GRID_LINE, (x, oy), (x, oy + L["gridH"]))

    def drawCellLabel(self, x, y, cell, text, fg):
        t = self.fontSm.render(text, True, fg)
        self.screen.blit(t, (x + cell // 2 - t.get_width() // 2,
                              y + cell // 2 - t.get_height() // 2))

    def drawPanel(self):
        L  = self._layout
        px = L["panelX"]
        ox = L["panelInner"]
        rw = L["panelRW"]
        sh = self.screenH

        pygame.draw.rect(self.screen, PANEL_BG,
                         pygame.Rect(px, 0, L["panelW"] + 16, sh))
        pygame.draw.line(self.screen, C_ACCENT, (px, 0), (px, sh), 2)

        def hline(y, col=C_ACCENT):
            pygame.draw.line(self.screen, col, (ox, y), (ox + rw, y), 1)

        def lbl(txt, x, y, font=None, col=C_SUBTEXT):
            self.screen.blit((font or self.fontSm).render(txt, True, col), (x, y))

        # Title
        lbl("PATH FINDER AI", ox, 16, self.fontHd, C_GOLD)
        hline(46)

        # Algorithm selector
        lbl("Search Algorithm:", ox, 52, self.fontSm, C_SUBTEXT)

        useHeuristic = self.dropdown.value in HEURISTIC_ALGOS
        if useHeuristic:
            lbl("Heuristic:", ox, 96, self.fontSm, C_SUBTEXT)

        # Coordinates - derive y from widget rects to stay in sync with updateLayout
        sepY = self.inpSr.rect.y - 8
        hline(sepY, (40, 40, 70))
        lbl("Start (r, c):", ox, self.inpSr.rect.y,  self.fontSm, C_SUBTEXT)
        lbl("Goal  (r, c):", ox, self.inpGr.rect.y, self.fontSm, C_SUBTEXT)
        for w in (self.inpSr, self.inpSc, self.inpGr, self.inpGc):
            w.draw(self.screen, self.fontMd)

        # Click hint
        hintY = self.inpGr.rect.bottom + 6
        hints = ["1) Click grid to set Start",
                 "2) Click grid to set Goal",
                 "Start & Goal set!  Press START"]
        hintCol = C_GREEN if self.clickPhase == 2 else (200, 200, 100)
        lbl(hints[min(self.clickPhase, 2)], ox, hintY, self.fontSm, hintCol)

        # Buttons
        self.btnStart.draw(self.screen, self.fontLg)
        self.btnPause.draw(self.screen, self.fontLg)
        self.btnReset.draw(self.screen, self.fontLg)

        # Speed slider
        sliderY = self.slider.rect.y
        hline(sliderY - 28, (40, 40, 70))
        lbl("Animation Speed:", ox, sliderY - 22, self.fontSm, C_SUBTEXT)
        self.slider.draw(self.screen, self.fontSm)

        # Statistics
        statsY = sliderY + 44
        hline(statsY)
        lbl("Statistics", ox, statsY + 6, self.fontLg, C_GOLD)
        sy = statsY + 34
        for k, v in self.stat.items():
            kt = self.fontSm.render(f"{k}:", True, C_SUBTEXT)
            vt = self.fontMd.render(v,        True, C_GOLD)
            self.screen.blit(kt, (ox, sy))
            self.screen.blit(vt, (ox + rw - vt.get_width(), sy))
            sy += 26

        # Status bar
        sy += 6
        hline(sy)
        sy += 8
        words, line = self.statusMsg.split(), ""
        for word in words:
            test = (line + " " + word).strip()
            if self.fontSm.size(test)[0] <= rw:
                line = test
            else:
                if line:
                    self.screen.blit(self.fontSm.render(line, True, C_GREEN), (ox, sy))
                    sy += 20
                line = word
        if line:
            self.screen.blit(self.fontSm.render(line, True, C_GREEN), (ox, sy))
            sy += 20

        # Optimal path banner
        if self.optimalPath is not None and not self.runningSim and self.stepCount > 0:
            sy += 6
            optLen = max(len(self.optimalPath) - 1, 0)
            if optLen == 0:
                hline(sy, C_ACCENT)
                sy += 8
                lbl("No optimal path exists", ox, sy, self.fontLg, C_ACCENT)
                sy += 26
                lbl("for this final state.", ox, sy, self.fontSm, C_ACCENT)
                sy += 22
            else:
                hline(sy, C_PATH)
                sy += 8
                lbl("Optimal Path Found!", ox, sy, self.fontLg, C_PATH)
                sy += 26
                lbl(f"Length: {optLen} steps", ox, sy, self.fontMd, C_PATH)
                sy += 24
                lbl("(shown in green on grid)", ox, sy, self.fontSm, (100, 210, 150))
                sy += 22

        # Colour legend
        sy += 6
        hline(sy, (50, 50, 80))
        sy += 8
        lbl("Legend", ox, sy, self.fontLg, C_GOLD)
        sy += 26
        legend = [
            (C_FREE,           "Free cell"),
            (C_BLOCKED,        "Blocked"),
            (C_START,          "Start (S)"),
            (C_GOAL,           "Goal (G)"),
            (C_AGENT,          "Agent"),
            ((255, 138, 128),  "Visited x1"),
            ((255,  82,  82),  "Visited x2"),
            ((255,  23,  68),  "Visited x3"),
            ((213,   0,   0),  "Visited x4"),
            (VISIT_5PLUS,      "Visited x5+"),
            (C_PATH,           "Optimal path"),
        ]
        for col, text in legend:
            if sy > sh - 20:
                break
            pygame.draw.rect(self.screen, col,          (ox,      sy, 18, 18))
            pygame.draw.rect(self.screen, (90, 90, 90), (ox,      sy, 18, 18), 1)
            self.screen.blit(self.fontSm.render(text, True, C_SUBTEXT), (ox + 26, sy + 1))
            sy += 22

        # Dropdowns
        if useHeuristic:
            self.ddHeuristic.draw(self.screen, self.fontMd)
        self.dropdown.draw(self.screen, self.fontMd)

if __name__ == "__main__":
    App().run()
