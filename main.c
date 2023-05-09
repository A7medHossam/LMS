#include "library_Managment_system.h"

int main()
{
    
    int id,choice,success; 
    
    char name[20],authorname[20];
    
    printf("\n*************** MAIN MENU ***************\n");
    printf("\n\t1. Add Books");
    printf("\n\t2. Delete books");
    printf("\n\t3. View Books");
    printf("\n\t4. Search book");
    printf("\n\t5. Issue books");
    printf("\n\t6. Close Application");
    printf("\n******************************************\n");
    printf("\n\tEnter your choice: ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        printf("\nBookId: ");
        scanf("%d",&id);
        fflush(stdin);
        printf("\nBook name:");
        //gets(name)
	    scanf("%19s",name);
        printf("Authorname: ");
        fflush(stdin);
        //gets(author)
	    scanf("%19s",authorname);
        success=addition(id,name,authorname);
        break;
        case 2:
        printf("\nBookId: ");
        scanf("%d",&id);
        success=deletebook(id);
        break;
        case 3:
        success=viewbook();
        break;
        case 4:
        printf("\nBookId:");
        scanf("%d",&id);
        success=searchbook(id);
        break;
        case 5:
        printf("\nBookId: ");
        scanf("%d",&id);
        success=issuebook(id);
        break;
        case 6:
        printf("\n\n\n");
        exit(1);
        default:
        printf("\n\tInvalid input");
        break;
     }
    if(success == pass)
    {
        printf("\nSuccessful\n");
    }
    else if(success==fail)
    {
        printf("Unsuccessful\n");
    }
    else{
        printf("Error\n");
    }
return 0;
}

// Add book
test_values addition(int id,char name[],char author[])
{
    
    
    
    FILE *fp=NULL;
    fp=fopen("bookLibrary.dat","ab+");
    
    if(fp == NULL)
    {
        printf("\nError: while opening file\n");
        return fail;
    }
    else{
        
        book *newBook = NULL;
        newBook = malloc(sizeof(book));
		
        newBook->book_id = id;
        strcpy(newBook->book_name,name);
        
    

    strcpy(newBook->author_name,author);
    
    fwrite(newBook,sizeof(book),1,fp);
    fclose(fp);
    free(newBook);
    
    
    return pass;
    }

}

// Delete book
test_values deletebook(int id)
{
    FILE *fp=NULL;
    FILE *ft=NULL;
    fp = fopen("bookLibrary.dat","rb");
    ft = fopen("temp.dat","wb");
    
    if(fp==NULL || ft==NULL)
        {
            printf("\nError: While opening file:\n");
            return fail;
        }
    else{
        rewind(fp);
        
        book *discarded_book = (book*)malloc(sizeof(book));
    while(fread(discarded_book,sizeof(book),1,fp)==1)
    {
        if(id != discarded_book->book_id)
        {  
            fwrite(discarded_book,sizeof(book),1,ft);
        }
        
    }
    fclose(fp);
    fclose(ft);
    free(discarded_book);
  
   remove("bookLibrary.dat");
    rename("temp.dat","bookLibrary.dat");
    
    return pass;
        }
}

// Issue book
test_values issuebook(int id)
{
    char name1[20];
    FILE *fp=NULL;
    fp = fopen("bookLibrary.dat","rb");
    if(fp==NULL)
    {
        printf("\nError while opening file in issuing book\\n");
        return fail;
    }
    else{

    scanf("%19s student name",name1);
    book *book_to_find=(book*)malloc(sizeof(book));
    while(fread(book_to_find,sizeof(book),1,fp))
    {
        if(book_to_find->book_id==id)
        {
            
            printf("\nBook_Id: %d\t\tBook_name: %s\t\tBook_Author: %s",book_to_find->book_id,book_to_find->book_name,book_to_find->author_name);
            printf("\n Book is issued to %s",name1);
            fclose(fp);
            free(book_to_find);
            return pass;
        }
    }

    fclose(fp);
    free(book_to_find);
    printf("\nSpecified book is not present\n");
    
    return fail;
    }
}

// Search book
test_values searchbook(int id)
{
    
    FILE *fp=NULL;
    fp = fopen("bookLibrary.dat","rb");
    if(fp==NULL)
    {
        printf("\nError while opening file in search area\n");
        return fail;
    }
    else{
    
    book *book_to_find=(book*)malloc(sizeof(book));
    while(fread(book_to_find,sizeof(book),1,fp))
    {
        if(book_to_find->book_id==id)
        {
            
            printf("\nBook_Id: %d\t\tBook_name: %s\t\tBook_Author: %s",book_to_find->book_id,book_to_find->book_name,book_to_find->author_name);
            fclose(fp);
            free(book_to_find);
            return pass;
        }
    }
    
    fclose(fp);
    free(book_to_find);
    printf("\nSpecified book is not present\n");
    
    return fail;
    }
}

// View book
test_values viewbook()
{
    
    FILE *fp=NULL;
    fp=fopen("bookLibrary.dat","rb");
   
    if(fp==NULL)
    {
        printf("\nERROR:\n");
        return fail;
    }
    else{
        book *book_to_find=(book*)malloc(sizeof(book));
    while(fread(book_to_find,sizeof(book),1,fp)==1)
    {
        printf("\n%d\t\t\t%s\t\t\t%s",book_to_find->book_id,book_to_find->book_name,book_to_find->author_name);
    }
    fclose(fp);
    free(book_to_find);
    
    return pass;
    }
}
