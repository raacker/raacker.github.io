---
title: "Multiple reduction using omp"
last_modified_at: 2019-12-12T19:30:15+09:00
categories:
    - "C++ / C#"
tags:
    - c++, omp, multithreading
---

Using omp for faster algorithm is now very common. Most of libraries you've ever heard will also using omp, I am, for sure, also using omp for various registrations or even any simple functions where I need more speed.

On this post, I'll summarize how I did multiple reduction to calculate min and max depth value at a same time which was quite a bit hard and buggy with internet examples.

To start, let's see a basic for loop that getting min value of an array.

{% highlight C++ %}
int arr[10]; //Some values inside
int min = INT_MAX;
for (int i = 0; i < 10; ++i)
{
    if (min > arr[i]) min = arr[i];
}
{% endhighlight %}

We can convert this for loop using reduction.

{% highlight C++ %}
int arr[10]; //Some values inside
int localMin = INT_MAX;
#pragma omp parallel for shared(local_min, arr) reduction(min : local_min)
    for (int i = 0; i < 10; ++i)
    {
        if (localMin > arr[i]) localMin = arr[i];
    }
{% endhighlight %}

What if we want to get min and max at the same time?

Originally, it should be

{% highlight C++ %}
int arr[10]; //Some values inside
int min = INT_MAX;
int max = INT_MIN;
for (int i = 0; i < 10; ++i)
{
    if (min > arr[i]) min = arr[i];
    if (max < arr[i]) max = arr[i];
}
{% endhighlight %}

But if you try to use reduction for both of them, compiler won't let you use both values at the same time.

{% highlight C++ %}
int arr[10]; //Some values inside
int localMin = INT_MAX;
int localMax = INT_MIN;
// ??????
#pragma omp parallel for shared(local_min, local_max, arr) reduction(min : local_min, max: local_max)
    for (int i = 0; i < 10; ++i)
    {
        if (localMin > arr[i]) localMin = arr[i];
        if (localMax < arr[i]) localMax = arr[i];
    }
{% endhighlight %}

To achieve, we should split omp parallel for loop into two section, the original for loop and critical section to sum up.

 Critical section is the spot that all of the omp threads are synchronized. So that, each thread will calculate its local min, max value and we can merge each thread's result into one place.

{% highlight C++ %}
int arr[10]; //Some values inside
int min = INT_MAX;
int max = INT_MIN;

// Wrap with parenthesis
#pragma omp parallel
{
    int localMin = INT_MAX;
    int localMax = INT_MIN;
#pragma omp for
    for (int i = 0; i < 10; ++i)
    {
        if (localMin > arr[i]) localMin = arr[i];
        if (localMax < arr[i]) localMax = arr[i];
    }

#pragma omp critical
    {
        if (min > localMin) min = localMin;
        if (max < localMax) max = localMax;
    }
}
{% endhighlight %}

Nice! we can apply this skill to our 8-bit depth map to get min & max depth value.

It's very much same as above code, except types :)

{% highlight C++ %}
unsigned char depthMap[imageSize];
unsigned char min = 255;
unsigned char max = 0;

// Wrap with parenthesis
#pragma omp parallel
{
    unsigned char localMin = 255;
    unsigned char localMax = 0;
#pragma omp for
    for (int i = 0; i < imageSize; ++i)
    {
        if (localMin > depthMap[i]) localMin = depthMap[i];
        if (localMax < depthMap[i]) localMax = depthMap[i];
    }

#pragma omp critical
    {
        if (min > localMin) min = localMin;
        if (max < localMax) max = localMax;
    }
}
{% endhighlight %}

You actually can apply this skill to various purpose since you don't need any special keys from omp.

Happy hacking!
