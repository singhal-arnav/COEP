#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <linux/fs.h>
#include "ext2_fs.h"

void read_super(int fd, struct ext2_super_block *sb) {
	lseek(fd, 1024, SEEK_SET);
	read(fd, sb, sizeof(struct ext2_super_block));
}

void read_group_desc(int fd, unsigned int block_size, unsigned int group_num, struct ext2_group_desc *bgdesc) {
	unsigned int gdt_offset;
	if(block_size == 1024)
		gdt_offset = 2048;
	else
		gdt_offset = block_size;
	lseek(fd, gdt_offset + group_num * sizeof(struct ext2_group_desc), SEEK_SET);
	read(fd, bgdesc, sizeof(struct ext2_group_desc));
}

void get_inode_data(int fd, unsigned int block_size, unsigned int inode_table, 
                    unsigned int inode_index, unsigned int inode_size, struct ext2_inode *inode) {
	unsigned int offset = inode_table * block_size + inode_index * inode_size;
	lseek(fd, offset, SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}

void display_inode_info(unsigned int inode_num, struct ext2_inode *inode) {
	int i;
	time_t atime, mtime, crtime;
	
	printf("\nInode %u\n", inode_num);
	printf("Mode: 0%o\n", inode->i_mode);
	printf("UID: %u\n", inode->i_uid);
	printf("GID: %u\n", inode->i_gid);
	printf("Size: %u bytes\n", inode->i_size);
	printf("Links count: %u\n", inode->i_links_count);
	printf("Blocks: %u\n", inode->i_blocks);
	printf("Flags: 0x%x\n", inode->i_flags);
	
	atime = (time_t)inode->i_atime;
	mtime = (time_t)inode->i_mtime;
	crtime = (time_t)inode->i_ctime;
	printf("Access time: %s", ctime(&atime));
	printf("Modify time: %s", ctime(&mtime));
	printf("Change time: %s", ctime(&crtime));
	
	printf("- Direct block pointers:\n");
	for(i = 0; i < EXT2_NDIR_BLOCKS; i++)
		if(inode->i_block[i] != 0)
			printf("    Block[%d]: %u\n", i, inode->i_block[i]);
	
	if(inode->i_block[EXT2_IND_BLOCK] != 0)
		printf("Single indirect block: %u\n", inode->i_block[EXT2_IND_BLOCK]);
	if(inode->i_block[EXT2_DIND_BLOCK] != 0)
		printf("Double indirect block: %u\n", inode->i_block[EXT2_DIND_BLOCK]);
	if(inode->i_block[EXT2_TIND_BLOCK] != 0)
		printf("Triple indirect block: %u\n", inode->i_block[EXT2_TIND_BLOCK]);
	printf("\n");
}

int main(int argc, char *argv[]) {
	int fd, inode_num;
	unsigned int block_size, inode_size, inodes_per_group;
	unsigned int group_num, inode_index;
	struct ext2_super_block sb;
	struct ext2_group_desc bgdesc;
	struct ext2_inode inode;
	
	fd = open(argv[1], O_RDONLY);
	inode_num = atoi(argv[2]);
	
	if(fd == -1) {
		perror("inodenumber:");
		exit(errno);
	}
	
	read_super(fd, &sb);
	block_size = 1024 << sb.s_log_block_size;
	inode_size = sb.s_inode_size;
	inodes_per_group = sb.s_inodes_per_group;
	
	group_num = (inode_num - 1) / inodes_per_group;
	inode_index = (inode_num - 1) % inodes_per_group;
	
	read_group_desc(fd, block_size, group_num, &bgdesc);
	get_inode_data(fd, block_size, bgdesc.bg_inode_table, inode_index, inode_size, &inode);
	
	display_inode_info(inode_num, &inode);
	
	close(fd);
	return 0;
}
