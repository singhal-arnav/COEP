#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/fs.h>
//#include <linux/ext2_fs.h>
#include "ext2_fs.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	int fd = open(argv[1], O_RDONLY); // argv[1] = /dev/sdb1
	int n = atoi(argv[2]); 
	int count, i;
	unsigned int block_size;
	struct ext2_super_block sb; 
	struct ext2_group_desc bgdesc;
	if(fd == -1) {
		perror("readsuper:");
		exit(errno);
	}
	
	lseek(fd, 1024, SEEK_CUR);
	count = read(fd, &sb, sizeof(struct ext2_super_block));
	block_size = 1024 << sb.s_log_block_size;
	
	if(block_size == 1024)
		lseek(fd, 2048, SEEK_SET);
	else
		lseek(fd, block_size, SEEK_SET);
	lseek(fd, n * sizeof(struct ext2_group_desc), SEEK_CUR);
	count = read(fd, &bgdesc, sizeof(struct ext2_group_desc));
	printf("Block Bitmap: %d\n", bgdesc.bg_block_bitmap);
	printf("Inode Bitmap: %d\n", bgdesc.bg_inode_bitmap);
	printf("Inode Table: %d\n", bgdesc.bg_inode_table);
	printf("Free Blocks Count: %d\n", bgdesc.bg_free_blocks_count);
	printf("Free Inodes Count: %d\n", bgdesc.bg_free_inodes_count);
	printf("Used Directories Count: %d\n", bgdesc.bg_used_dirs_count);
	printf("Padding: %d\n", bgdesc.bg_pad);

	close(fd); 
}
