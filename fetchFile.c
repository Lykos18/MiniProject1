int fileFetchPrint(int){
FILE *fp;
  //open a file in read mode;
fp = fopen("test.txt", "r");
//Store the file contents in an array
char fileString[100];
//Read the content and store it in the strng
while (fgets(fileString, 100, fp)) {
 //print  the file content
printf("%s", fileString); 
}
//Close the file
fclose(fp);
}
