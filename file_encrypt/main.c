#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>

//PROTOTYPES
void handle_arguments (int argc, char **argv);
int count_file_length (FILE * f);
void read_file(FILE * file, char *contents);
int write_file (char *path, char *contents, int char_count);
void exclusiveor (char *file_contents, char *op_result, char *key, int clength, int klength);
void generate_key(char *key, int content_length);
FILE * open_file (char * path);
int take_user_input(void);
//takes commandline arguments and handles them
//this handles exit values and stdout messages
void handle_arguments (int argc, char **argv)
{
  if(argc < 4 || argc > 5)
  {
    fprintf(stderr, "Usage: operation file output_location [key]\n");
    exit(1);
  }
}

void generate_key(char *key, int content_length)
{
  int divisor = (int) RAND_MAX/127;
	int num, i;
	
  for(i = 0; i<content_length; i++)
  {
		do {
			num = rand() / divisor;
		} while (num > 127|| num < 0);
		key[i] = num;
  }

}

//
FILE* open_file (char * path)
{
	FILE * f = fopen(path, "r");
	if(f == NULL)
  {
    perror("oops");
  }
	return f;
}
//return 1 if succeed or 0 if failed
/**
* @param path - path to file to be read
* @param contents - array to store the contents of said file
* @return int - number of characters in file
*/
int count_file_length (FILE * file)
{
  
  //get char count
  int char_count = 0;
  while(!feof(file))
  {
    int c = fgetc(file);
    char_count++;
  }
  rewind(file);

  return char_count;
}



//read the contents of a file to an array
void read_file (FILE * file, char * contents) 
{
  
  int index = 0;
  while(1) 
  {
    int c = fgetc(file);
    if (feof(file))
      break;
    contents[index] = c;
    index++;
  } 
  fclose(file); 
}

/**
* @param path - path to write to
* @param contents -
*/
int write_file (char *path, char *contents, int char_count)
{
  FILE *wfile = fopen(path, "w");
  if(wfile == NULL)
  {
    fprintf(stderr, "Unable to open file for write\n");
    fclose(wfile);
    return 0;
  }
  int i;
  for(i = 0; i < char_count; ++i)
  {
    fputc(contents[i], wfile);
  }
  fclose(wfile);
  fprintf(stderr, "Save complete\n");
  return 1;
}


//this implementation uses an XOR cipher.
void exclusiveor (char *file_contents, char *op_result, char *key, int clength, int klength)
{
  int i;
	for (i = 0; i<clength; i++)
	{
		op_result[i] = file_contents[i] ^ key[i];
	}


}

int take_user_input (void)
{
	return 0;
}

/**
* @param argv[1] - char distinguishing whether the file is to be encrypted or decrypted.
* @param argv[2] filename
* @param argv[3] output folder
* @param argv[4] key location
*/
int main(int argc, char *argv[], char **envp)
{
  handle_arguments(argc, argv);
	
  //file_contents after it has been either encrypted or decrypted
  
  //get contents of file to encrypt or decrypt
	FILE * plaintext_file = open_file(argv[2]);
	if (plaintext_file == NULL)
		exit(7);
  int content_length = count_file_length(plaintext_file);
  char contents[content_length];
  char op_result[content_length];
  int k_length;
	char key[content_length];
  read_file(plaintext_file, contents);
	
  if (argv[1][0] == 'e')
  {		//generate a key
		char key[content_length];
    generate_key(key, content_length);
    exclusiveor(contents, op_result, key, content_length, content_length);
		take_user_input();
		write_file("/home/thomas/Desktop/keyfile.txt", key, content_length);
  } else if (argv[1][0] == 'd')
  {		//read key
    FILE * k_file = open_file(argv[4]);
		k_length = count_file_length(k_file);
		
		read_file(k_file, key);
    exclusiveor(contents, op_result, key, content_length, k_length);
  }
	
  //check it was successful perhaps
  write_file(argv[3], op_result, content_length);
  return 0;
}
