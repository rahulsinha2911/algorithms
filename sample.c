  /*
     * C program to accept N numbers and arrange them in an ascending order
     */
 
    #include <stdio.h>
    int main()
    {
 
        int i, j, a, n, number[30];
        printf("Enter the value of N \n");
        scanf("%d", &n);
 
        printf("Enter the numbers \n");
        for (i = 0; i < n; ++i)
            scanf("%d", &number[i]);
 
        for (i = 0; i < n; ++i) 
        {
 
            for (j = i + 1; j < n; ++j)
            {
 
                if (number[i] > number[j]) 
                {
 
                    a =  number[i];
                    number[i] = number[j];
                    number[j] = a;
 
                }
 
            }
 
        }
 
        printf("The numbers arranged in ascending order are given below \n");
        for (i = 0; i < n; ++i)
            printf("%d\n", number[i]);
 
    }
    
    
    
  
  
  
  
  
 // C program to change case from upper to lower and lower to upper

#include <stdio.h>
 
int main ()
{
   int c = 0;
   char ch, s[1000];
 
   printf("Input a string\n");
   gets(s);
   
   while (s[c] != '\0') {
      ch = s[c];
      if (ch >= 'A' && ch <= 'Z')
         s[c] = s[c] + 32;
      else if (ch >= 'a' && ch <= 'z')
         s[c] = s[c] - 32;  
      c++;  
   }
   
   printf("%s\n", s);
 
   return 0;
}  
    
    
    
    

//Example: Store Information in Structure and Display it   
   
#include <stdio.h>
struct student
{
    char name[50];
    int roll;
    float marks;
} s[10];

int main()
{
    int i;

    printf("Enter information of students:\n");

    // storing information
    for(i=0; i<10; ++i)
    {
        s[i].roll = i+1;

        printf("\nFor roll number%d,\n",s[i].roll);

        printf("Enter name: ");
        scanf("%s",s[i].name);

        printf("Enter marks: ");
        scanf("%f",&s[i].marks);

        printf("\n");
    }

    printf("Displaying Information:\n\n");
    // displaying information
    for(i=0; i<10; ++i)
    {
        printf("\nRoll number: %d\n",i+1);
        printf("Name: ");
        puts(s[i].name);
        printf("Marks: %.1f",s[i].marks);
        printf("\n");
    }
    return 0;
}
