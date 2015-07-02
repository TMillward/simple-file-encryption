#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mcrypt.h>

#include <math.h>
#include <stdint.h>

!!GENERATE public and private keys, store public key in a file, user keeps private key
FILE *file;
//PROTOTYPES
void handle_arguments (int argc, char* argv);
int read_file (char *path, char *contents);
int write_file (char *path, char *contents, int char_count);
int exclusiveor (char *file_contents, char *op_result, int *key);

void generate_key(char *key, int content_length)
//takes commandline arguments and handles them
//this handles exit values and stdout messages
void handle_arguments (int argc, char* argv)
{
  if(argc < 3 || argc > 4)
  {
    fprintf(stderr, "Usage: operation file output_location [key]\n");
    exit(1);
  }
  if (argv[1])
  {
    //check operation is valid
    exit(2);
  }
}

void generate_key(char *key, int content_length)
{

}

//return 1 if succeed or 0 if failed
/**
* @param path - path to file to be read
* @param contents - array to store the contents of said file
* @return int - number of characters in file
*/
int read_file (char *path, char *contents)
{
  if(!(file = fopen(path, "r")))
  {
    //failed to open
    fclose(file);
    return 0;
  }
  //get char count
  int char_count = 0;
  while(1)
  {
    int c = fgetc(file);
    if(c == EOF)
      break;
    char_count++;
  }
  rewind(file);
  //for each line:
    //malloc an array (will need to establish line length first)
    //ALWAYS FREE MALLOCED MEMORY
  if (char_count % 2 == 0)
  {//to make key generation easier we want the contents array to have an even size
    contents = (char *)malloc(char_count*SIZEOF(char));
  } else
  {
    char_count++;
    contents = (char *)malloc((char_count)*SIZEOF(char));
  }
  //want the key and the contents to be able to be xored, hence set to '0'
  memset(contents, '0', char_count);
  int index = 0;
  while(1)//good lord refactor this
  {
    int c = fgetc(file);
    if (c == EOF)
      break;

    contents[index] = (char)c;
    index++;
  }
  return char_count;
}

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
  for(i = 0; i <char_count; ++i)
  {
    fputc(contents[i]);
  }
  fclose(wfile);
  fprintf(stderr, "Save complete\n");
  return 1;
}
//this implementation uses an XOR cipher.
int exclusiveor (char *file_contents, char *op_result, int *key)
{
  return 0;
}


/**
* @param argv[1] - char distinguishing whether the file is to be encrypted or decrypted.
* @param argv[2] filename
* @param argv[3] output folder
* @param argv[4] key location
*/
int main(int argc, char *argv[], char**envp)
{
  handle_arguments(argv);
  int content_lenth;
  char *file_contents;
  char *key;
  //file_contents after it has been either encrypted or decrypted
  char *op_result;
  //get contents of file to encrypt oro decrypt
  content_length = read_file(argv[2], file_contents);
  if (argv[1][0] == 'e')
  {//generate a key
    generate_key(key, content_length);
    exclusiveor(file_contents, op_result, key);
  } else if (argv[1][0] == 'd')
  {//read key
    readfile(argv[4], key);
    exclusiveor(file_contents, op_result, key);
  }
  free(file_contents);
  //check it was successful perhaps
  write_file(argv[3], op_result, content_length);
  free(op_result);
  return 0;
}
