import random
import math

class LinearRegression:
    def _init_(self):
        self.coefficients = []
        self.intercept = 0
        self.mean = []
        self.std = []

    def normalize(self, X):
        self.mean = [sum(col) / len(col) for col in zip(*X)]
        self.std = [math.sqrt(sum((x - m) ** 2 for x in col) / len(col)) for col, m in zip(zip(*X), self.mean)]
        return [[(x - m) / s if s != 0 else 0 for x, m, s in zip(row, self.mean, self.std)] for row in X]

    def fit(self, X, y):
        X_normalized = self.normalize(X)
        X_with_intercept = [[1] + row for row in X_normalized]
        n_features = len(X_with_intercept[0])
        self.coefficients = [0] * n_features
        learning_rate = 0.01
        iterations = 10000

        for _ in range(iterations):
            for i in range(len(X)):
                y_pred = sum(self.coefficients[j] * X_with_intercept[i][j] for j in range(n_features))
                error = y_pred - y[i]
                for j in range(n_features):
                    self.coefficients[j] -= learning_rate * error * X_with_intercept[i][j]

        self.intercept = self.coefficients[0]
        self.coefficients = self.coefficients[1:]

    def predict(self, X):
        X_normalized = [[(x - m) / s if s != 0 else 0 for x, m, s in zip(row, self.mean, self.std)] for row in X]
        return [sum(self.coefficients[j] * X_normalized[i][j] for j in range(len(self.coefficients))) + self.intercept for i in range(len(X))]

random.seed(0)
n_samples = 1000

square_footage = [random.randint(1000, 5000) for _ in range(n_samples)]
bedrooms = [random.randint(1, 6) for _ in range(n_samples)]
bathrooms = [random.randint(1, 4) for _ in range(n_samples)]
price = [100000 + 100 * sf + 25000 * bed + 35000 * bath + random.gauss(0, 50000) 
         for sf, bed, bath in zip(square_footage, bedrooms, bathrooms)]

X = list(zip(square_footage, bedrooms, bathrooms))
y = price

train_size = int(0.8 * n_samples)
X_train, X_test = X[:train_size], X[train_size:]
y_train, y_test = y[:train_size], y[train_size:]

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)

mse = sum((y_pred[i] - y_test[i])**2 for i in range(len(y_test))) / len(y_test)
r2 = 1 - sum((y_pred[i] - y_test[i])*2 for i in range(len(y_test))) / sum((y_test[i] - sum(y_test)/len(y_test))*2 for i in range(len(y_test)))

print(f"Mean squared error: {mse:.2f}")
print(f"R-squared score: {r2:.2f}")

print("\nModel coefficients:")
for feature, coef in zip(['square_footage', 'bedrooms', 'bathrooms'], model.coefficients):
    print(f"{feature}: {coef:.2f}")
print(f"Intercept: {model.intercept:.2f}")

new_house = [[2500, 3, 2]]
predicted_price = model.predict(new_house)
print(f"\nPredicted price for a 2500 sq ft house with 3 bedrooms and 2 bathrooms: ${predicted_price[0]:,.2f}")
