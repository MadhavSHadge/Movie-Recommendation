# Movie Recommendation System

## Overview
This program implements a simple movie recommendation system using the Pearson correlation to calculate similarities between users. The program reads user-movie ratings from a CSV file, predicts ratings for unrated movies, and provides top-N movie recommendations for a specific user.

---

## Features
1. **Load Ratings**: Reads a CSV file containing user-movie ratings and stores them in a 2D vector.
2. **Calculate Similarity**: Computes the Pearson correlation coefficient to measure similarity between users based on their ratings.
3. **Predict Ratings**: Estimates a user's rating for a movie based on weighted averages of ratings from similar users.
4. **Recommend Movies**: Generates a list of top-N recommended movies for a specific user.

---

## Input Format
- The ratings are stored in a CSV file, where each row represents a user, and each column represents a movie. Ratings are integers (e.g., 1 to 5), and a value of `0` indicates that a movie has not been rated by a user.

### Example CSV File (`ratings.csv`):
```
5,3,0,1
4,0,0,1
1,1,0,5
0,0,5,4
```
- This file represents 4 users and 4 movies.

---

## How to Use

### 1. Compile and Run
Compile the program using a C++ compiler (e.g., `g++`) and run the executable:
```bash
$ g++ -o recommend recommend.cpp
$ ./recommend
```

### 2. User Input
The program prompts the user to enter:
1. The index of the user (0-based).
2. The number of top recommendations (N).

### 3. Output
The program outputs the top-N recommended movies for the selected user along with the predicted ratings.

---

## Code Breakdown

### Functions
1. **`loadRatings`**
   - Loads the CSV file containing ratings.
   - Updates the number of users and movies.

2. **`calculateSimilarity`**
   - Computes Pearson correlation between two users based on their shared ratings.

3. **`predictRating`**
   - Predicts the rating of a movie for a specific user by considering the ratings from similar users.

4. **`recommendMovies`**
   - Recommends top-N movies for a user based on predicted ratings.

### Main Function
- Reads the input CSV file.
- Prompts the user for input (user index and number of recommendations).
- Calls the `recommendMovies` function and displays the results.

---

## Example Run
### Input:
```
Enter user index (0 to 3): 1
Enter number of top recommendations (N): 2
```
### Output:
```
Top 2 recommended movies for User 1:
Movie 2 with predicted rating: 4.5
Movie 1 with predicted rating: 4.2
```

---

## Notes
- The program assumes a valid and well-formed CSV file.
- Users are indexed starting from 0.
- Movies are also indexed starting from 0.
- The recommendation system only considers unrated movies for predictions.

---

## Possible Improvements
- Add error handling for invalid input.
- Support larger datasets by optimizing similarity calculations.
- Include additional similarity measures, such as cosine similarity.
- Provide movie titles by mapping indices to a metadata file.

---

## Dependencies
- Standard C++ libraries: `<iostream>`, `<vector>`, `<fstream>`, `<sstream>`, `<cmath>`, `<algorithm>`.

---

## License
This project is open-source and available for modification and distribution under the MIT License.

