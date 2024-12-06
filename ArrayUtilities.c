// header file
#include "ArrayUtilities.h"

// constants defined here
const int CELL_WIDTH = 5;
const int MAX_ARRAY_SIDE = 25;
const int MIN_ARRAY_SIDE = 3;

const char THICK_DIVIDER_LINE = '=';
const char THIN_DIVIDER_LINE = '-';

int **clearTwoDimArray( int **array, int numCols )
   {
    int colIndex;

    for( colIndex = 0; colIndex < numCols; colIndex++ )
       {
        free( array[ colIndex ] );
       }

    free( array );

    return NULL;
   }

void copyArray( int **destArray, int **srcArray, int numRows, int numCols )
   {
     // declare variables
     int newRows, newCols;
     // loop through rows
     for(newRows = 0; newRows < numRows; newRows++)
        {
          // loop through columns
          for(newCols = 0; newCols < numCols; newCols++)
            {
              // put element from source array and put into dest array
              destArray[newRows][newCols] = srcArray[newRows][newCols];
              // end column loop
            }
            // end row loop
        }
   }

int **createTwoDimArray( int numRows, int numCols )
   {
    int **twoDimPtr;
    int rowIndex, colIndex;

    twoDimPtr = (int **)malloc( numRows * sizeof( int *) );

    for( rowIndex = 0; rowIndex < numRows; rowIndex++ )
       {
        twoDimPtr[ rowIndex ] = (int *)malloc( numCols * sizeof( int ) );

        for( colIndex = 0; colIndex < numCols; colIndex++ )
           {
            twoDimPtr[ rowIndex ][ colIndex ] = 0;
           }
       }

    return twoDimPtr;
   }

void displayArray( int **array, int numRows, int numCols, char *title )
   {
      // declare variables
      int rowIndex, colIndex;
      // print title
       printf("\nArray Display - %s\n", title);
      // display table
        // print the first thick line
         // function: displayDividerLine
       displayDividerLine(numCols, THICK_DIVIDER_LINE);
        // loop through the rows
        for(rowIndex = 0; rowIndex < numRows; rowIndex++)
         {
           // print thin lines except for the first line
            // function: displayDividerLine
           if(rowIndex != 0)
             {
               displayDividerLine(numCols, THIN_DIVIDER_LINE);
             }
             // print the first pipe
               // function: printf
             printf("%c", PIPE);
           // loop through the columns
           for(colIndex = 0; colIndex < numCols; colIndex++)
             {
               // check if the element is over 0
                 // if it is, print the element
                 if(array[rowIndex][colIndex] > 0)
                  {
                    printf("%5d ", array[rowIndex][colIndex]);
                  }
                  // otherwise print the asterisks
                  else
                  {
                      printf("  *** ");
                  }
                  // print the next pipe
                  printf("%c", PIPE);
              // end the column loop
             }
               printf("%c", NEWLINE_CHAR);
          // end the row loop
         }
        // print ending line; thick line
         // function: displayDividerLine
        displayDividerLine(numCols, THICK_DIVIDER_LINE);

   }
void displayDividerLine( int horizNumCells, char thicknessChar )
   {
      // define variables
        int index;
      // print the first pipe
        printf("%c", PIPE);
      // loop through the number of cells
        for(index = 0; index < horizNumCells; index++)
          {
             // print the dashed lines
               // function: printChars
               printChars(CELL_WIDTH, thicknessChar);
             // print the next pipe
              // function: printf
              printf("%c", PIPE);
            // end loop
          }
          // go to the next line
            // function: printf
          printf("%c", NEWLINE_CHAR);
   }

int getArraySide( int maxSideSize )
   {
     // declare variable to store input
       int size = 0;

     // create a loop that prompts user until data is valid
     // prompt user for array size
      printf("Enter array side (%d - %d): ", MIN_ARRAY_SIDE, MAX_ARRAY_SIDE);
       do
        {
         // store user input in the size variable
          // function: scanf
           scanf("%d", &size);
         // test the user input to see if it's in range
           if( size < MIN_ARRAY_SIDE || size > maxSideSize )
            {
              // if condtional is true, then display error message
               // function: printf
              printf("Incorrect entry - Enter array side (%d - %d): ", \
                      MIN_ARRAY_SIDE, MAX_ARRAY_SIDE);
            }
         }
         // the user is prompted for valid data until condition isn't true
         while ( size < MIN_ARRAY_SIDE || size > maxSideSize );
         // print new line
         printf("%c", NEWLINE_CHAR);
         // return user input
         return size;
   }

int getRandBetween( int lowLimit, int highLimit )
   {
    int range = highLimit - lowLimit + 1;

    return rand() % range + lowLimit;
   }

void getRangeToRemove( RangeType *inputData, int numRows, int numCols )
   {
      // initialize variables
      int maxSide = numRows * numCols;
     // print the subsection title
       // function: printf
       printf("Range Removal Entry:\n");

     // create a nested loop that prompts user for low and high limits
      // and tests if the number is in range
     do
       {
            do
               {
                 // prompt user for low limits
                  // function: printf
                  printf("    - Enter low limit (1 - %d): ", maxSide);
                 // store user input in variable
                  // function: scanf
                  scanf("%d", &inputData->lowVal);
                  // test user input to see if in range
                  if(inputData->lowVal < 1 || inputData->lowVal > maxSide)
                    {
                      // show error message if condition is true
                        // function: printf
                      printf("--- Incorrect entry - Retry: \n");
                      // end test
                    }
               }
               while (inputData->lowVal < 1 || inputData->lowVal > maxSide);
                 // prompts user for high limits
                   // function: printf
                 printf("    - Enter high limit (%d - %d): ", \
                                           inputData->lowVal + 1, maxSide);
                // store user input in variable
                 // function: scanf
                 scanf("%d", &inputData->highVal);
                // test user input to see if in range
                 if(inputData->highVal < inputData->lowVal + 1 || \
                                           inputData->highVal > maxSide)
                  {
                    // show error message if conditional is true
                     // function: printf
                    printf("--- Incorrect entry - Retry: \n");
                    // end test
                  }
                  // end loop
               }
               while(inputData->highVal < inputData->lowVal + 1 || \
                                                inputData->highVal > maxSide);
   }
bool isInArray( int **array, int numRows, int numCols, int searchVal )
   {
     // declare variables
     int rCount, cCount;
     // loop through the rows
     for(rCount = 0; rCount < numRows; rCount++)
       {
         // loop through the columns
         for(cCount = 0; cCount < numCols; cCount++)
           {
             // test if element is in array
             if(array[rCount][cCount] == searchVal)
               {
                 // return true if condition is valid
                 return true;
                 // end test
               }
               // end loop for columns
           }
           // end loop for rows
       }
       // return false otherwise
       return false;
   }
void loadArrayWithValues( int **array, int numRows, int numCols )
   {
     // initialize variables
     int rowIndex, colIndex, newValue;
     // loop across the rows
     for(rowIndex = 0; rowIndex < numRows; rowIndex++)
       {
         // loop across the columns
         for(colIndex = 0; colIndex < numCols; colIndex++ )
           {
               // loop until random value is unique
                 // function: isInArray
              do
                {
                  // generate new value
                   // function: getRandBetween
                  newValue = getRandBetween(1, numRows*numCols);

                }
                while(isInArray(array, numRows, numCols, newValue));
               // set unique value to array
                array[rowIndex][colIndex] = newValue;
             // end column loop
           }
         // end row loop
       }
   }
void printChars( int numChars, char outChar )
   {
    if( numChars > 0 )
       {
        printChars( numChars - 1, outChar );
       }

    printf( "%c", outChar );
   }
void removeRange( int **array, int numRows, int numCols, RangeType range )
   {
      // initialize variables
       int index;
      // loop from lowest to highest value (inclusive)
      for(index = range.lowVal; index <= range.highVal; index++)
        {
          // set the element in range to zero
           // function: setElementToZero
           setElementToZero(array, numRows, numCols, index);
        }
   }
bool setElementToZero( int **array, int numRows, int numCols, int searchValue )
   {
     // declare variables
     int countRows, countCols;
     // loop through the rows
     for(countRows = 0; countRows < numRows; countRows++)
       {
         // loop through the columns
         for(countCols = 0; countCols < numCols; countCols++)
           {
             // test if searchValue is found
               if(array[countRows][countCols] == searchValue)
                {
                  // set element to zero
                  array[countRows][countCols] = 0;
                  // return true
                  return true;
                  // end test
                }
            // end loop for columns
           }
          // end loop for rows
       }
       return false;
   }
