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
	int fd = open(argv[1], O_RDONLY); // argv[1] = /dev/sdb1
	int n = atoi(argv[2]); 
	int count, i;
	unsigned int block_size, inode_size, inodes_per_group, inode_blocks;
	struct ext2_super_block sb; 
	struct ext2_group_desc bgdesc;
	if(fd == -1) {
		perror("nthblock:");
		exit(errno);
	}
	
	lseek(fd, 1024, SEEK_CUR);
	count = read(fd, &sb, sizeof(struct ext2_super_block));
	block_size = 1024 << sb.s_log_block_size;
	inode_size = sb.s_inode_size;
	inodes_per_group = sb.s_inodes_per_group;
	inode_blocks = (inodes_per_group * inode_size + block_size - 1) / block_size;
	
	if(block_size == 1024)
		lseek(fd, 2048, SEEK_SET);
	else
		lseek(fd, block_size, SEEK_SET);
	count = read(fd, &bgdesc, sizeof(struct ext2_group_desc));
	
	unsigned int first_data_block = bgdesc.bg_inode_table + inode_blocks;
	unsigned int target_block = first_data_block + n;
	char *data_block = (char *)malloc(block_size + 1);
	lseek(fd, target_block * block_size, SEEK_SET);
	read(fd, data_block, block_size);
	data_block[block_size] = '\0';
	printf("Reading the nth data block:\n");
	fwrite(data_block, 1, block_size, stdout);
	printf("\n");

	close(fd); 
}
