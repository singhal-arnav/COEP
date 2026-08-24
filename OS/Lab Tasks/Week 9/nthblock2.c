#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/fs.h>
#include "ext2_fs.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	int fd = open(argv[1], O_RDONLY);
	int n = atoi(argv[2]);
	int count;
	unsigned int block_size, inode_size, inodes_per_group, inode_blocks, blocks_per_group, group, index;
	struct ext2_super_block sb;
	struct ext2_group_desc bgdesc;

	if (fd == -1) {
		perror("nthblock:");
		exit(errno);
	}

	lseek(fd, 1024, SEEK_SET);
	read(fd, &sb, sizeof(struct ext2_super_block));
	block_size = 1024 << sb.s_log_block_size;
	inode_size = sb.s_inode_size;
	inodes_per_group = sb.s_inodes_per_group;
	blocks_per_group = sb.s_blocks_per_group;
	inode_blocks = (inodes_per_group * inode_size + block_size - 1) / block_size;

	group = n / blocks_per_group;
	index = n % blocks_per_group;

	if (block_size == 1024)
		lseek(fd, 2048 + group * sizeof(struct ext2_group_desc), SEEK_SET);
	else
		lseek(fd, block_size + group * sizeof(struct ext2_group_desc), SEEK_SET);
	read(fd, &bgdesc, sizeof(struct ext2_group_desc));

	unsigned int first_data_block = bgdesc.bg_inode_table + inode_blocks;
	unsigned int target_block = first_data_block + index;
	char *data_block = malloc(block_size + 1);
	lseek(fd, (off_t)target_block * block_size, SEEK_SET);
	read(fd, data_block, block_size);
	data_block[block_size] = '\0';
	fwrite(data_block, 1, block_size, stdout);

	close(fd);
	free(data_block);
}
