# **Multi-objective least squares and applications**

## Introduction

This is an introductory article designed to introduce readers with some basic programming background to the multi-objective least squares problem. The Table of Contents:

* Preliminaries
* Multi-objective least squares
* Regularized data fitting
* An interesting Application


## Preliminaries

Before we start, you need to review some fundamental concepts that we will use later on.

* Basic Linear Algebra
* Least Squares

## Multi-objective least squares

In a multi-objective least squares problem, we want to seek one $x$ that minimizes a linear combination of $n$ objectives at the same time.

$$J_1 = ||A_1x-b_1||^2, J_2 = ||A_2x-b_2||^2, ..., J_n = ||A_nx-b_n||^2$$

For example, a weighted least squares problem can be formulated with the above definitions.

$$ \textnormal{minimize} \quad J = \lambda_1||A_1x-b_1||^2 + ... + \lambda_n||A_nx-b_n||^2$$

In general, the coefficients $\lambda_1, ..., \lambda_n$ are positive values, and they express the relative importance of different objectives. An extreme example is $\lambda_1 = 1, \lambda_{2}, ..., \lambda_{n} = 0$, which simplifies this problem to a single-objective least squares problem.

*** 

### Solution of weighted least squares

Assuming all $\lambda$s are all positive, we can slightly rewrite the objective.

$$ \begin{aligned}
\textnormal{minimize} \quad J &= \lVert\sqrt{\lambda_{1}}A_1x-\sqrt{\lambda_1}b_1 \rVert^2 + ... + \lVert\sqrt{\lambda_{n}}A_nx-\sqrt{\lambda_n}b_n \rVert^2\\
&= \sum_{k=1}^{n} \lVert\sqrt{\lambda_{k}}A_kx-\sqrt{\lambda_k}b_k \rVert^2\\
&= \lVert 
\begin{bmatrix}
\sqrt{\lambda_{1}}A_1 \\
\sqrt{\lambda_{2}}A_2 \\
\vdots\\
\sqrt{\lambda_{n}}A_n
\end{bmatrix} x - 
\begin{bmatrix}
\sqrt{\lambda_{1}}b_1 \\
\sqrt{\lambda_{2}}b_2 \\
\vdots\\
\sqrt{\lambda_{n}}b_n
\end{bmatrix} \rVert^2
\end{aligned}
$$

We can see that in the final form, it looks exactly like a least squares problem. However, if the stacked matrix has linearly dependent columns, we have multiple solutions. Also note that we do not enforce all matrices $A$ to be full column rank, i.e. have linearly independent columns.

Hence the solution to the above least squares problem can be derived from a single-objective least squares problem.

$$\hat{x} = (\lambda_1A_1^TA_1+...+\lambda_kA_k^TA_k)^{-1}(\lambda_1A_1^Tb_1+...+\lambda_kA_k^Tb_k)$$

## Regularized data fitting

**Motivation**. In a simple linear (linear in parameters!) regression problem, we have data points $(x^{(1)}, y^{(1)}), (x^{(2)}, y^{(2)}), (x^{(3)}, y^{(3)}), ..., (x^{(N)}, y^{(N)})$ and model
 $$\hat{f}(x)=\theta_1f_1(x)+...+\theta_pf_p(x)$$

If $\hat{f}_k(x)$ is a high-order polynomial of x, then a large $\theta_k$ will amplify the perturbations in $x$. This will result in a large variance in $\hat{f}(x)$, hence an overfitted model. We will later see how this is useful in image deblurring.

***

**Problem**. Now, our problem becomes two-fold: 
1) We want to fit the model $\hat{f}(x)$ to data points $(x^{(1)}, y^{(1)}), (x^{(2)}, y^{(2)}), (x^{(3)}, y^{(3)}), ..., (x^{(N)}, y^{(N)})$, i.e. minimize the difference between our prediction and ground-truth.
2) We want to keep $\theta_1, \theta_2, ..., \theta_p$ small to avoid over-fitting.

**Method**. We can easily formulate this problem into a multi-objective least squares problem.

$$J_1(\theta) = \sum_{k=1}^{N}(\hat{f}(x^{(k)}) - y^{(k)})^2,\quad J_2(\theta) = \sum_{j=1}^{p}\theta_j^2$$

Depending on the strength of regularization, we can increase/decrease the value of a regularization coefficient $\lambda$. That is,

$$ \begin{aligned}
\textnormal{minimize} \quad J_1(\theta) + \lambda J_2(\theta) &= \sum_{k=1}^{N}(\hat{f}(x^{(k)}) - y^{(k)})^2 + \lambda \sum_{j=1}^{p}\theta_j^2 \\
&= \lVert
\begin{bmatrix}
A_1 \\
\sqrt{\lambda}A_2 \\
\end{bmatrix} \theta - 
\begin{bmatrix}
y^d\\
0\\
\end{bmatrix}
\rVert^2
\end{aligned}
$$

$$\textnormal{with} \quad y^d = (y^{(1)}, ..., y^{(N)}), \quad
A_1 = 
\begin{bmatrix}
1 & f_2(x^{(1)}) & \cdots & f_p(x^{(1)}) \\
1 & f_2(x^{(2)}) & \cdots & f_p(x^{(2)}) \\
\vdots & \vdots & \ddots & \vdots \\
1 & f_2(x^{(N)}) & \cdots & f_p(x^{(N)}) \\
\end{bmatrix}, \quad
A_2 = 
\begin{bmatrix}
0 & 1 & 0 & \cdots & 0 \\
0 & 0 & 1 & \cdots & 0 \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
0 & 0 & 0 & \cdots & 1 \\
\end{bmatrix}
$$

***

**Solution**. Similar to the previous multi-objective least squares problem:

$$\hat{x} = (A_1^TA_1 + \lambda A_2^TA_2)^{-1}(A_1^Ty^d)$$

## An interesting application

In this part, we will briefly discuss how we can treat some problems in real life as multi-objective least squares problems.

***

An interesting application of estimation (or multi-objective least squares problem) is image deblurring/denoising. 

Let $x_{ex}$ be an unknown image and y be an observed image.

In the MATLAB code below, we load in an image from the USC-SIPI Image Database at <http://sipi.usc.edu/database>.

```Matlab
% MATLAB script
using MAT, ImageView
f = matopen("deblur.mat");
Y = read(f, "Y");
B = read(f, "B");
imshow(Y);
```
<p align="center">
    <img src="../Images/blurry_image.png"
    width="50%" height="50%">
    <figcaption> Fig.1 blurry image Y</figcaption>
</p>

**Problem**. In this image deblurring problem, we are given a noisy and blurred image $Y$, which comes from a clear yet unknown image $x_{ex}$. We can model this transformation as $Y = Ax_{ex} + n$, where $A$ is a known blurring matrix and $n$ is unknown noise. 

**Method**. We will try to construct $\hat{x}$ so that 1) we can get a denoised image, and 2) the image doesn't seem blurry.

We will introduce the cost function/objective:

$$\textnormal{minimize} \quad J_1 + J_2 = \lVert Ax - y \rVert^2 + \lambda(\lVert D_vx\rVert^2 + \lVert D_hx \rVert^2) $$

$$\textnormal{where} \quad \lVert D_vx\rVert^2 + \lVert D_hx \rVert^2 = \sum_{i=1}^{M}\sum_{j=1}^{N-1}(X_{i, j+1}-X_{i,j})^2+\sum_{i=1}^{M-1}\sum_{j=1}^{N}(X_{i+1, j}-X_{i,j})^2$$

**Intuition**. The term $\lVert D_vx\rVert^2 + \lVert D_hx \rVert^2$ represents the sum of squared differences between values at neighboring (both vertical and horizontal) pixels. If this term is small, then it means that the neighboring pixels transition smoothly. If this term is large, then $\hat{x}$ would look like an mosaic image.

```Matlab
% MATLAB script (cont.)
E = [1, zeros(1, 1023); zeros(1022, 1024); -1, zeros(1, 1023)];
D = @(lambda) abs(fft2(B)).^2 + lambda.*abs(fft2(E)).^2 + lambda.*abs(fft2(E')).^2;

for i=-6:2:0
  X = ifft2((conj(fft2(B)).*fft2(Y))./D(10.^i));
  figure();
  imshow(X);
  str = sprinf('lambda=%d',i);
  title(str);
end
```
<p align="center">
    <img src="../Images/nonblurry_image.png" 
    width="80%" height="80%">
    <figcaption> Fig.2 Deblurred images </figcaption>
</p>

**Analysis**. In the above code, we used Fast Fourier Transform and Inverse Fast Fourier Transform to help us deblur the image. This is out of the scope of this wiki. We notice that when $\lambda = 10^{-6}$, the deblurred image looks like a mosaic image. It's similar to "overfitting" in regression problems as this cost function disregards the variance of pixel differences. On the other hand, when $\lambda = 1$, the cost function penalizes any abrupt changes in neighboring pixel values, resulting in a "smoothed" image.


## Reference

Boyd, S., &amp; Vandenberghe, L. (2019). Chapter15: Multi-objective Least Squares. In Introduction to applied linear algebra: Vectors, matrices, and least squares (pp. 309–325). essay, Cambridge University Press. 

Unclear, U. (n.d.). Volume1: Mosaics. Sipi Image Database. Retrieved February 10, 2023, from http://sipi.usc.edu/database 

Johari, A. (2020, May 13). A 101 guide on the least squares regression method. Medium. Retrieved February 10, 2023, from https://medium.com/edureka/least-square-regression-40b59cca8ea7 