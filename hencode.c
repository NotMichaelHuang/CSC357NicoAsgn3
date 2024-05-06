#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "hencode.h"
#include "huffman.h"

#define MAXIMUM_ARGS 3
#define MINIMUM_ARGS 2
#define FILE_ERR 0


int main(int argc, char **argv)
{
	int fd_in;
	int fd_out;
	char *file_in;
	char *file_out;
	
	/* -1 indicated the value to false */
	fd_in = FALSE;
	fd_out = FALSE;

	/* Maximum arguemtns and stuff */
	if(argc > MAXIMUM_ARGS)
	{
			fprintf(stderr, IN_ERR);
			exit(EXIT_FAILURE);
	}	

	/* Get the in st4ream */
	file_in = argv[1];	
	fd_in = open(file_in, O_RDONLY);
	if(fd_in < FILE_ERR)
	{		
			perror(IN_ERR);
			exit(EXIT_FAILURE);
	}

	/* get the out stream */
	if(argc > MINIMUM_ARGS)
	{
		file_out = argv[2];
		fd_out = open(file_out, O_WRONLY);
		if(fd_out < FILE_ERR)
		{
			perror(IN_ERR);
			exit(EXIT_FAILURE);	
		}
	}
	else
	{
		fd_out = STDOUT_FILENO;
	}
	/* Encoding... */
	hencode(fd_in, fd_out);
	
	close(fd_in);
	close(fd_out);
	return EXIT_SUCCESS;
}


void hencode(int fin, int fout)
{
	/* Increase buffer size to 4096 */
	unsigned char byte[1] = {'\0'};	
	unsigned char c;
	short iterate;
	char *sorted_string;
	DataNode *nodes;

	/* init */
	c = FALSE;
	iterate = FALSE;
	sorted_string = NULL;
	nodes = NULL;
	
	nodes = create_node();
	while(read(fin, &byte, 1) > 0)
	{
		/* Acceptable values for unsigned c w/o demotion or promotion */ 
		c = byte[0];
		insert_node(c, nodes);
	}
	sort_list(nodes);	
	sorted_string = link_to_array(nodes);
	nodes = build_tree(nodes);
	
	iterate = 0;
	while(sorted_string[iterate] != '\0')
	{
		char *f_str;
		char *p_path;		
		char node_char;
		int f_length;

		f_str = NULL;
		p_path = NULL;	
		node_char = FALSE;
		f_length = FALSE;

		node_char = sorted_string[iterate];
		p_path = dfs(nodes, node_char);	

		/* Format the string */		
		/* asprintf is safer than sprintf int terms of it will allocate 
 		 * malloc for you :) and you get the length too!!!!
 		 * */
		/* TODO get rid off */
		/*
		f_length = asprintf(&f_str, "%#04x: %s\n", node_char, p_path);	
		*/
		printf("%s\n", p_path);
	
		write(fout, f_str, f_length);
		free(f_str);
		f_str = NULL;
		p_path = NULL;
		f_length = FALSE;
		iterate++;
	}

	free_list(nodes);
	free_string(sorted_string);
}


