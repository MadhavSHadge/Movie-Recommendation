#include <iostream> 
#include <vector> 
#include <fstream> 
#include <sstream> 
#include <cmath> 
#include <algorithm> 
 
// Function to load ratings from a CSV file into a 2D vector 
std::vector<std::vector<int>> loadRatings(const std::string& filename, int& numUsers, int& numMovies) { 
    std::ifstream file(filename); 
    std::vector<std::vector<int>> ratings; 
    std::string line; 
 
    if (!file.is_open()) { 
        std::cerr << "Error opening file" << std::endl; 
        return ratings; 
    } 
 
    while (std::getline(file, line)) { 
        std::vector<int> row; 
        std::stringstream ss(line); 
        int rating; 
        while (ss >> rating) { 
            row.push_back(rating); 
            if (ss.peek() == ',') ss.ignore(); 
        } 
        ratings.push_back(row); 
    } 
     
    numUsers = ratings.size(); 
    numMovies = ratings[0].size(); 
    return ratings; 
} 
 
// Function to calculate Pearson correlation between two users 
double calculateSimilarity(const std::vector<int>& user1, const std::vector<int>& user2) { 
    double sumXY = 0, sumX2 = 0, sumY2 = 0; 
    int count = 0; 
 
    for (size_t i = 0; i < user1.size(); ++i) { 
        if (user1[i] > 0 && user2[i] > 0) {  // Only consider rated movies 
            sumXY += (user1[i] * user2[i]); 
            sumX2 += (user1[i] * user1[i]); 
            sumY2 += (user2[i] * user2[i]); 
            ++count; 
        } 
    } 
 
    if (count == 0) return 0;  // No common ratings 
 
    double numerator = sumXY - (sumX2 * sumY2 / count); 
    double denominator = sqrt((sumX2 - (sumX2 * sumX2 / count)) * (sumY2 - (sumY2 * sumY2 / count))); 
 
    return (denominator == 0) ? 0 : numerator / denominator; 
} 
 
// Function to predict the rating for a specific user and movie 
double predictRating(const std::vector<std::vector<int>>& ratings, int userIndex, int movieIndex, int numUsers) { 
    double weightedSum = 0; 
    double totalWeight = 0; 
 
    for (int i = 0; i < numUsers; ++i) { 
        if (i != userIndex && ratings[i][movieIndex] > 0) { 
            double similarity = calculateSimilarity(ratings[userIndex], ratings[i]); 
            weightedSum += similarity * ratings[i][movieIndex]; 
            totalWeight += fabs(similarity); 
        } 
    } 
 
    return (totalWeight == 0) ? 0 : (weightedSum / totalWeight); 
} 
 
// Function to generate top N movie recommendations for a given user 
std::vector<std::pair<int, double>> recommendMovies(const std::vector<std::vector<int>>& ratings, int userIndex, int N) { 
    std::vector<std::pair<int, double>> recommendations; 
 
    for (size_t movieIndex = 0; movieIndex < ratings[userIndex].size(); ++movieIndex) { 
        if (ratings[userIndex][movieIndex] == 0) {  // Only consider unrated movies 
            double predictedRating = predictRating(ratings, userIndex, movieIndex, ratings.size()); 
            if (predictedRating > 0) { 
                recommendations.push_back({movieIndex, predictedRating}); 
            } 
        } 
    } 
 
    // Sort recommendations by predicted rating in descending order 
    std::sort(recommendations.begin(), recommendations.end(), [](const auto& a, const auto& b) { 
        return a.second > b.second; 
    }); 
 
    if (recommendations.size() > N) { 
        recommendations.resize(N); 
    } 
 
    return recommendations; 
} 
 
int main() { 
    int numUsers, numMovies; 
    std::vector<std::vector<int>> ratings = loadRatings("ratings.csv", numUsers, numMovies); 
 
    if (ratings.empty()) { 
        std::cerr << "No data loaded" << std::endl; 
        return 1; 
    } 
 
    int userIndex; 
    std::cout << "Enter user index (0 to " << numUsers - 1 << "): "; 
    std::cin >> userIndex; 
 
    int topN; 
    std::cout << "Enter number of top recommendations (N): "; 
    std::cin >> topN; 
 
    std::vector<std::pair<int, double>> recommendations = recommendMovies(ratings, userIndex, topN); 
 
    std::cout << "Top " << topN << " recommended movies for User " << userIndex << ":\n"; 
    for (const auto& rec : recommendations) { 
        std::cout <<"Movie " << rec.first << " with predicted rating: " << rec.second << std::endl; 
    } 
 
    return 0; 
}