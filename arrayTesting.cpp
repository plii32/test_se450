#include <deepstate/DeepState.hpp>
#include "ArrayUtilities.h"

using namespace deepstate;

#define MAX_ROWS 25
#define MAX_COLS 25

// Test for creating and clearing a 2D array
TEST(ArrayUtilitiesTest, CreateAndClearArray) {
    // Generate random rows and columns
    int numRows = DeepState_IntInRange(3, MAX_ROWS);  // Random number of rows
    int numCols = DeepState_IntInRange(3, MAX_COLS);  // Random number of columns

    // Create a 2D array with the generated size
    int** array = createTwoDimArray(numRows, numCols);
    
    // Log the size of the created array
    LOG(TRACE) << "Created 2D array with dimensions: %d" << numRows << "x %d" << numCols;
    // LOG(TRACE) << "a[" << i << "] = " << a[i];

    // Assert that the array was created correctly
    ASSERT_NE(array, nullptr);
    
    // Now clear the array
    array = clearTwoDimArray(array, numCols);
    
    // Assert that the array is cleared (it should be NULL now)
    ASSERT_EQ(array, nullptr);
}

// Test for copying a 2D array
TEST(ArrayUtilitiesTest, CopyArray) {
    // Generate random rows and columns
    int numRows = DeepState_IntInRange(3, MAX_ROWS);  // Random number of rows
    int numCols = DeepState_IntInRange(3, MAX_COLS);  // Random number of columns

    // Create two 2D arrays: source and destination
    int** sourceArray = createTwoDimArray(numRows, numCols);
    int** destArray = createTwoDimArray(numRows, numCols);

    // Fill the source array with random values
    loadArrayWithValues(sourceArray, numRows, numCols);

    // Log the values being copied
    //DeepState_StreamFormat(DEEPSTATE_LOG_INFO, "Copying array from source to destination");

    // Copy the source array to the destination array
    copyArray(destArray, sourceArray, numRows, numCols);

    // Assert that the destination array has the same values as the source
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            ASSERT_EQ(destArray[row][col], sourceArray[row][col]);
        }
    }

    // Clean up
    clearTwoDimArray(sourceArray, numCols);
    clearTwoDimArray(destArray, numCols);
}

// Test for loading an array with random values
TEST(ArrayUtilitiesTest, LoadArrayWithValues) {
    // Generate random rows and columns
    int numRows = DeepState_IntInRange(3, MAX_ROWS);  // Random number of rows
    int numCols = DeepState_IntInRange(3, MAX_COLS);  // Random number of columns

    // Create a 2D array with the generated size
    int** array = createTwoDimArray(numRows, numCols);

    // Load the array with random values
    loadArrayWithValues(array, numRows, numCols);

    // Log the values in the array
    //DeepState_StreamFormat(DEEPSTATE_LOG_INFO, "Loaded array with random values");

    // Assert that the array is filled with non-zero values
    bool valuesFilled = true;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (array[row][col] == 0) {
                valuesFilled = false;
                break;
            }
        }
        if (!valuesFilled) break;
    }

    ASSERT_TRUE(valuesFilled);

    // Clean up
    clearTwoDimArray(array, numCols);
}

// Test for removing a range of values from the array
TEST(ArrayUtilitiesTest, RemoveRangeFromArray) {
    // Generate random rows and columns
    int numRows = DeepState_IntInRange(3, MAX_ROWS);  // Random number of rows
    int numCols = DeepState_IntInRange(3, MAX_COLS);  // Random number of columns

    // Create a 2D array with the generated size
    int** array = createTwoDimArray(numRows, numCols);

    // Load the array with random values
    loadArrayWithValues(array, numRows, numCols);

    // Define the range to remove
    RangeType range;
    range.lowVal = DeepState_IntInRange(1, numRows * numCols);
    range.highVal = DeepState_IntInRange(range.lowVal, numRows * numCols);

    // Log the range to remove
    //DeepState_StreamFormat(DEEPSTATE_LOG_INFO, "Removing range: %d to %d", range.lowVal, range.highVal);
    LOG(TRACE) << "Removing range: " << range.lowVal << " to " << range.highVal;
    // Remove the specified range
    removeRange(array, numRows, numCols, range);

    // Assert that the elements in the range are set to zero
    for (int i = range.lowVal; i <= range.highVal; ++i) {
        ASSERT_TRUE(setElementToZero(array, numRows, numCols, i));
    }

    // Clean up
    clearTwoDimArray(array, numCols);
}
