


# Introduction to Machine Learning Classification: K-Nearest Neighbors  
*by Jonathan Lai*
	
## Introduction

Machine learning has been around for quite some time now, but has had many advancements in recent years. Applications of machine learning nowadays are plentiful and diverse, from being used in the corporate world to filter through job applications to being used by vehicles to autonomously navigate to their destination. ChatGPT, “an AI-powered chatbot,” which has been all the hype these recent months, also has its roots in machine learning (Hetler). Okay, so machine learning has many practical applications, but what exactly is machine learning and how does it work? In this article, I will discuss the fundamentals concepts of machine learning and then also explore these concepts by going through a concrete example of a machine learning algorithm known as K-Nearest Neighbors.

## Machine Learning Classification

There are multiple categories of machine learning, but for this discussion, I will focus on classification, where the goal is determine (or classify) which type something belongs to. For example, a classification problem we could be trying to solve is: given a flower with some known petal width and sepal length, what species is it amongst Setosa, Versicolor, and Virginica? With machine learning, we would want to be able to input the values of the petal width and sepal length into our **model** and then have it return us with the species that the flower belongs to. First, however, we need to discuss what a machine learning model is, what it means to train it, and then ultimately how it's used for classification.

To classify using machine learning, we must first **train** a **model** and then use it to **classify**. For a concrete definition, a **machine learning model** is one that can be “trained to recognize certain types of patterns (QuinnRadich).” Once trained, the model should then be able to be used to classify, or guess the **label** of unknown data. Training a machine learning model requires data and an algorithm for which you want the model to learn the data by. For the flower classification example above, the data we could provide the model to train the data is just a list of flowers, their corresponding petal width and sepal lengths (which we call **features**), and then their actual, true species type (their **labels**). Then with this and an algorithm to interpret this data, we would ultimately have a model that could be used for predicting flower species based on a given petal width and sepal length. There are many machine learning algorithms out there that each have their own way to train a model and use it to classify, but the one I will talk about today is k-Nearest Neighbors, or k-NN.

## K-Nearest Neighbors Algorithm

The **k-Nearest Neighbors** machine learning algorithm is one that uses “**proximity** to make predictions about a data point (What Is).” The training process of the k-Nearest Neighbors is one of the more simple ones amongst machine learning algorithms, involving only storing the training data into some data structure (e.g., a list). Then, with this data, the algorithm predicts the label of a given data point whose label is unknown (which we are trying to classify) by guessing that it is the labels of the points closest to it. Conceptually, this algorithm relies on the heuristic that if a data point lies close to other data points of a certain label, it is likely that this new data point would also be of that same label. This heuristic does not always hold, but works for a decent number of cases. For example, if the Versicolor species of flower tends to have small petal widths but the Setosa species tends to have large petal widths, then when a new data point comes in, a flower with small petal width, kNN would deem it to be Versicolor, which would likely be correct (shown in figure 1).

![](https://lh6.googleusercontent.com/JaZFQ7XEaimw2qvIeq2d4VD3iyUUYnQwNzD4VhI2AiHcc9wloBxnkGB_8v2XYtw2kUrRSJPPOqVAyhtL7aWEEGUsVemhnfkT6SgLsmFJDPs1htymLaBnamFP2wXtt0aZNsPvVxyA-834My0HbB_Xp2Q)

Going more in-depth of how classification works in kNN, the ‘k’ in k-Nearest Neighbors determines how many known data points the algorithm should check before determining what the label is of this new data point. For example, if k is 1, then for classification, the algorithm would deem that the label of the unknown data point is that of its closest neighbor (the data point closest to it). In other words, it would find the known data point (from the list of data points given) closest to the one we are trying to classify and return its label. In figure 2, the new **example**, or unknown data point to classify, would be considered class A, since that is the closest point. It gets more complicated when k is increased, but the algorithm is still just finding the k nearest points and classifying the new point as the majority label amongst those.![](https://lh4.googleusercontent.com/rXApVbI6bdtaZgrKGbrgcImfaZXabj5UmQxvVAB5_ZojyHThZOP7i31g3oCkZgyuIJhyQa4xu7ksZDTSiYr3FLynGVr2s5BSK0isocoMgJnBaaFbw741YiN_Noqcr1PpdUqGZtkQNi7VjlJfGZacKTQ)

## Closing Remarks

What we have discussed is a very basic machine learning algorithm that can be used for classification, but there are many more out there including neural networks, soft vector machines, etc, that could be used for different purposes like regression (as opposed to classification). Furthermore, in this discussion, you may have noticed that kNN requires **labeled data** to make decisions, as in, we require the data to come with labels that we already know. This category of machine learning algorithm is called **supervised learning**. There exists, in machine learning, **unsupervised learning** algorithms that could even train on data without these labels and still be able to classify, such as EM (Expectation-Minimization) or K-Means. In any case, there are lots more in the machine learning world but hopefully this gives you enough prerequisite information to head out and start exploring.

## Citations

Hetler, Amanda. “Bard vs. CHATGPT: What's the Difference?” WhatIs.com, TechTarget, 8 Feb. 2023, [https://www.techtarget.com/whatis/feature/Bard-vs-ChatGPT-Whats-the-difference](https://www.techtarget.com/whatis/feature/Bard-vs-ChatGPT-Whats-the-difference).

QuinnRadich. “What Is a Machine Learning Model?” Microsoft Learn, [https://learn.microsoft.com/en-us/windows/ai/windows-ml/what-is-a-machine-learning-model](https://learn.microsoft.com/en-us/windows/ai/windows-ml/what-is-a-machine-learning-model)

“What Is the K-Nearest Neighbors Algorithm?” IBM, [https://www.ibm.com/topics/knn](https://www.ibm.com/topics/knn).

[Figure (2)] Navlani, Avinash. “KNN Classification Using Scikit-Learn.” Medium, Artificial Intelligence in Plain English, 19 Jan. 2021, [https://ai.plainenglish.io/knn-classification-using-scikit-learn-efb34151a8b9](https://ai.plainenglish.io/knn-classification-using-scikit-learn-efb34151a8b9).
