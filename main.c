#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char* title;
    char* author;
    char* publisher;
    char* coverType;
    int price;
    int numberOfPages;
    int publishingYear;
}Book;

typedef struct BookArray{
    Book* list;
    size_t size;
}Array;

void list(Array* array){
    if(array->size == 0)
        printf("No books to show!\n");
    else{
        for(int i = 0; i < array->size; i++){
            printf("Book: %d,\n"
                   "Title: %s, Author: %s,\n"
                   "Publisher: %s, Cover: %s,\n"
                   "Price: %d, Pages: %d, Year: %d\n\n",i,array->list[i].title, array->list[i].author, array->list[i].publisher, array->list[i].coverType, array->list[i].price, array->list[i].numberOfPages, array->list[i].publishingYear);
        }
    }
}

void modify(Array* array){
    if(array->size == 0)
        printf("No books to modify!\n");
    else{
        printf("Type the number of the book you would like to modify\n");
        for(int i = 0; i < array->size; i++){
            printf("Book %d: %s\n",i,array->list[i].title);
        }
        int index;
        scanf("%d",&index);
        printf("What do you want to modify from Book %d?\n", index);
        printf("To modify the title, type 1\n"
               "To modify the author, type 2\n"
               "To modify the publisher, type 3\n"
               "To modify the cover, type 4\n"
               "To modify the price, type 5\n"
               "To modify the number of pages, type 6\n"
               "To modify the publishing year, type 7\n");
        int attribute;
        scanf("%d",&attribute);
        switch (attribute) {
            case 1:
                printf("Type the new title of the book\n");
                char new1[50];
                scanf ("%s", new1);
                strcpy(array->list[index].title,new1);
                break;
            case 2:
                printf("Type the new author of the book\n");
                char new2[50];
                scanf("%s",new2);
                strcpy(array->list[index].author,new2);
                break;
            case 3:
                printf("Type the new publisher of the book\n");
                char new3[50];
                scanf("%s",new3);
                strcpy(array->list[index].publisher,new3);
                break;
            case 4:
                printf("Type the new cover type of the book\n");
                char new4[50];
                scanf("%s",new4);
                strcpy(array->list[index].coverType,new4);
                break;
            case 5:
                printf("Type the new price of the book\n");
                int new5;
                scanf("%d",&new5);
                array->list[index].price = new5;
                break;
            case 6:
                printf("Type the new number of pages of the book\n");
                int new6;
                scanf("%d",&new6);
                array->list[index].numberOfPages = new6;
                break;
            case 7:
                printf("Type the new publishing year of the book\n");
                int new7;
                scanf("%d",&new7);
                array->list[index].publishingYear = new7;
                break;
            default:
                printf("don't recognize this command");
                break;
        }
    }
}

void delete(Array* array){
    if(array->size == 0)
        printf("No books to delete!\n");
    else{
        printf("What book would you like to delete?\n");
        for(int i = 0; i < array->size; i++){
            printf("Book %d: %s\n",i,array->list[i].title);
        }
        int index;
        scanf("%d",&index);
        free(array->list[index].title);
        free(array->list[index].author);
        free(array->list[index].publisher);
        free(array->list[index].coverType);
        for(int i = index; i < array->size; i++)
            array->list[i] = array->list[i+1];
        array->size = array->size - 1;
    }
}

size_t getNumberOfBooks(FILE *fptr){
    int counter=0,character;
    for (character = getc(fptr); character != EOF; character = getc(fptr))
        if (character == '\n') // Increment count if this character is newline
            counter = counter + 1;
    return counter;
}

void initArray(Array* array, size_t initialSize){
    array->list = (Book*) malloc(initialSize * sizeof(struct Book));
    array->size = initialSize;

    memset(&array->list[0], 0, sizeof(Book) * initialSize);
}

void initialAdd(Array *array, Book bookToAdd, int position){
    array->list[position].title = (char*) malloc(strlen(bookToAdd.title)+1);
    strcpy(array->list[position].title, bookToAdd.title);

    array->list[position].author = (char*) malloc(strlen(bookToAdd.author)+1);
    strcpy(array->list[position].author, bookToAdd.author);

    array->list[position].publisher = (char*) malloc(strlen(bookToAdd.publisher)+1);
    strcpy(array->list[position].publisher, bookToAdd.publisher);

    array->list[position].coverType = (char*) malloc(strlen(bookToAdd.coverType)+1);
    strcpy(array->list[position].coverType, bookToAdd.coverType);

    array->list[position].price = bookToAdd.price;
    array->list[position].numberOfPages = bookToAdd.numberOfPages;
    array->list[position].publishingYear = bookToAdd.publishingYear;
}

void addBook(Array *array, Book* bookToAdd){
    (array->size)++;
    array->list = (Book*) realloc(array->list, (array->size) * sizeof(Book));
    memset(&array->list[array->size+1], 0, sizeof(Book));

    array->list[array->size-1].title = (char*) malloc(strlen(bookToAdd->title)+1);
    //strcpy(array->list[array->size].title, bookToAdd.title);
    array->list[array->size-1].title = bookToAdd->title;


    array->list[array->size-1].author = (char*) malloc(strlen(bookToAdd->author)+1);
    //strcpy(array->list[array->size].author, bookToAdd.author);
    array->list[array->size-1].author = bookToAdd->author;

    array->list[array->size-1].publisher = (char*) malloc(strlen(bookToAdd->publisher)+1);
    //strcpy(array->list[array->size].publisher, bookToAdd.publisher);
    array->list[array->size-1].publisher = bookToAdd->publisher;

    array->list[array->size-1].coverType = (char*) malloc(strlen(bookToAdd->coverType)+1);
    //strcpy(array->list[array->size].coverType, bookToAdd.coverType);
    array->list[array->size-1].coverType = bookToAdd->coverType;

    array->list[array->size-1].price = bookToAdd->price;
    array->list[array->size-1].numberOfPages = bookToAdd->numberOfPages;
    array->list[array->size-1].publishingYear = bookToAdd->publishingYear;
}

void startOperations(Array* array){
    printf("If you want to add a book, type \"1\"\n"
           "If you want to see the list of books, type \"2\"\n"
           "If you want to modify something about a currently listed book, type \"3\"\n"
           "If you want to delete a listed book, type \"4\"\n");
    int opInput;
    scanf("%d",&opInput);
    switch (opInput) {
        case 1:
            printf("Type in the information you want to add\n");
            Book book;
            book.title = (char*) malloc(50*sizeof(char));
            book.author = (char*) malloc(50*sizeof(char));
            book.publisher = (char*) malloc(50*sizeof(char));
            book.coverType = (char*) malloc(20*sizeof(char));
            char buff[50];
            fgets(buff,50,stdin);
            fgets(book.title,50,stdin);
            book.title[strlen(book.title)-1] = 0;
            fgets(book.author,50,stdin);
            book.author[strlen(book.author)-1] = 0;
            fgets(book.publisher,50,stdin);
            book.publisher[strlen(book.publisher)-1] = 0;
            fgets(book.coverType,50,stdin);
            book.coverType[strlen(book.coverType)-1] = 0;
            scanf("%d",&book.price);
            scanf("%d",&book.numberOfPages);
            scanf("%d",&book.publishingYear);
            //scanf("%50[^,],%50[^,],%50[^,],%10[^,],%d,%d,%d", book.title, book.author, book.publisher, book.coverType, &book.price, &book.numberOfPages, &book.publishingYear);
            //book.title++;
            addBook(array,&book);
            printf("If you want to do something else, type \"1\"\n"
                   "If you want to stop here, type \"2\"\n");
            int addInput;
            scanf("%d",&addInput);
            if(addInput==1){
                startOperations(array);
                break;
            }

            else
                printf("Have a nice day!");
            break;
        case 2:
            list(array);
            printf("If you want to do something else, type \"1\"\n"
                   "If you want to stop here, type \"2\"\n");
            int listInput;
            scanf("%d",&listInput);
            if(listInput==1){
                startOperations(array);
                break;
            }

            else
                printf("Have a nice day!");
            break;
        case 3:
            modify(array);
            printf("If you want to do something else, type \"1\"\n"
                   "If you want to stop here, type \"2\"\n");
            int modInput;
            scanf("%d",&modInput);
            if(modInput==1){
                startOperations(array);
                break;
            }
            else
                printf("Have a nice day!");
            break;
        case 4:
            delete(array);
            printf("If you want to do something else, type \"1\"\n"
                   "If you want to stop here, type \"2\"\n");
            int delInput;
            scanf("%d",&delInput);
            if(delInput==1){
                startOperations(array);
                break;
            }
            else
                printf("Have a nice day!");
            break;
        default:
            printf("don't recognize this command");
    }
}

void freeArray(Array* array){
    for(int i = 0; i < array->size; i++){
        free(array->list[i].title);
        array->list[i].title = NULL;
        free(array->list[i].title);
        free(array->list[i].author);
        array->list[i].author = NULL;
        free(array->list[i].author);
        free(array->list[i].publisher);
        array->list[i].publisher = NULL;
        free(array->list[i].publisher);
        free(array->list[i].coverType);
        array->list[i].coverType = NULL;
        free(array->list[i].coverType);
    }
    free(array->list);
    array->list = NULL;
    free(array->list);
    array->size = 0;
}

int main() {
    //Opens file
    FILE *filePointer;
    filePointer = fopen("C:\\Users\\user\\CLionProjects\\Bookshop_Different\\data.txt","r");

    if(filePointer == NULL){
        printf("File doesn't exist\n");
        exit(1);
    }

    //Initializes array
    Array bookList;
    size_t numberOfBooks = getNumberOfBooks(filePointer);
    rewind(filePointer);
    initArray(&bookList,numberOfBooks);

    //Allocates memory and inserts the elements from the file into the array
    Book book;
    book.title = (char*) malloc(50*sizeof(char));
    book.author = (char*) malloc(50*sizeof(char));
    book.publisher = (char*) malloc(50*sizeof(char));
    book.coverType = (char*) malloc(20*sizeof(char));
    int i = 0;
    while(fscanf(filePointer, "%50[^,],%50[^,],%50[^,],%10[^,],%d,%d,%d\n", book.title, book.author, book.publisher, book.coverType, &book.price, &book.numberOfPages, &book.publishingYear) == 7){
        initialAdd(&bookList,book,i);
        i++;
    }
    free(book.title);
    book.title = NULL;
    free(book.title);
    free(book.author);
    book.author = NULL;
    free(book.author);
    free(book.publisher);
    book.publisher = NULL;
    free(book.publisher);
    free(book.coverType);
    book.coverType = NULL;
    free(book.coverType);
    startOperations(&bookList);
    freeArray(&bookList);
    return 0;
}
