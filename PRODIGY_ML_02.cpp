#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm>

struct Customer {
    double total_spent;
    int num_purchases;
};

struct Centroid {
    double total_spent;
    int num_purchases;
};

double euclidean_distance(const Customer& a, const Centroid& b) {
    return std::sqrt(std::pow(a.total_spent - b.total_spent, 2) +
                     std::pow(a.num_purchases - b.num_purchases, 2));
}

std::vector<Centroid> initialize_centroids(const std::vector<Customer>& customers, int k) {
    std::vector<Centroid> centroids;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, customers.size() - 1);

    for (int i = 0; i < k; ++i) {
        int idx = dis(gen);
        centroids.push_back({customers[idx].total_spent, customers[idx].num_purchases});
    }

    return centroids;
}

std::vector<int> assign_clusters(const std::vector<Customer>& customers,
                                 const std::vector<Centroid>& centroids) {
    std::vector<int> clusters(customers.size());

    for (size_t i = 0; i < customers.size(); ++i) {
        double min_distance = std::numeric_limits<double>::max();
        int cluster = 0;

        for (size_t j = 0; j < centroids.size(); ++j) {
            double distance = euclidean_distance(customers[i], centroids[j]);
            if (distance < min_distance) {
                min_distance = distance;
                cluster = j;
            }
        }

        clusters[i] = cluster;
    }

    return clusters;
}

std::vector<Centroid> update_centroids(const std::vector<Customer>& customers,
                                       const std::vector<int>& clusters,
                                       int k) {
    std::vector<Centroid> new_centroids(k, {0, 0});
    std::vector<int> cluster_sizes(k, 0);

    for (size_t i = 0; i < customers.size(); ++i) {
        int cluster = clusters[i];
        new_centroids[cluster].total_spent += customers[i].total_spent;
        new_centroids[cluster].num_purchases += customers[i].num_purchases;
        cluster_sizes[cluster]++;
    }

    for (int i = 0; i < k; ++i) {
        if (cluster_sizes[i] > 0) {
            new_centroids[i].total_spent /= cluster_sizes[i];
            new_centroids[i].num_purchases /= cluster_sizes[i];
        }
    }

    return new_centroids;
}

std::vector<int> k_means_clustering(const std::vector<Customer>& customers, int k, int max_iterations) {
    std::vector<Centroid> centroids = initialize_centroids(customers, k);
    std::vector<int> clusters;

    for (int iteration = 0; iteration < max_iterations; ++iteration) {
        std::vector<int> new_clusters = assign_clusters(customers, centroids);
        
        if (new_clusters == clusters) {
            break;
        }

        clusters = new_clusters;
        centroids = update_centroids(customers, clusters, k);
    }

    return clusters;
}

int main() {
    std::vector<Customer> customers = {
        {100, 5}, {200, 10}, {50, 2}, {300, 15}, {150, 8},
        {80, 4}, {250, 12}, {180, 9}, {120, 6}, {220, 11}
    };

    int k = 3;
    int max_iterations = 100;

    std::vector<int> clusters = k_means_clustering(customers, k, max_iterations);

    std::cout << "Customer clusters:" << std::endl;
    for (size_t i = 0; i < customers.size(); ++i) {
        std::cout << "Customer " << i + 1 << " (Total spent: " << customers[i].total_spent
                  << ", Num purchases: " << customers[i].num_purchases
                  << ") - Cluster: " << clusters[i] + 1 << std::endl;
    }

    return 0;
}