---
title: "TMIOS Design Pattern, 16 - Iterator"
last_modified_at: 2022-11-10T20:59:00-08:00
categories:
    - designpattern
tags:
    - [Design Pattern, TMIOS]
excerpt: "Teach me in one sentence, Design Pattern series - Iterator"
toc: true
---

# Iterator

> GoF Numbering : 16<br/>
> Category : Behavioral Pattern<br/>
> Readings : [Wikipedia](https://en.wikipedia.org/wiki/Iterator_pattern), 
[DigitalOcean](https://www.digitalocean.com/community/tutorials/iterator-design-pattern-java), 
[cs.unc.edu](https://www.cs.unc.edu/~stotts/GOF/hires/pat5dfso.htm),
[Refactoring.guru](https://refactoring.guru/design-patterns/iterator)<br/>
> As known as : Cursor, Pointer

## In One Sentence

Traverse a container's elements using a same interface for all different kinds of container.

> Post officers who can drive Motorcycle, Small Delivery car, or even Truck visit every house in order. They don't have to care about what the posts have inside and which vehicle they use. They just visit and drop off.

## Problem

Do you know which is the fastest data structure to traverse all the elements among Fixed Size Array, Dynamic Size Array, Linked Node List, Binary Search Tree, or any other traversal data structures?

I even don't know. Then we better test to see what's the actual difference. Isn't it?

*This is a concept code*
```c++
#include "Timer.h"
#include "DataStructures.h"
#include <vector>
#include <iostream>

using namespace std;

void printValue(const int& value)
{
    std::cout << value << std::endl;
}

int main()
{
    std::vector<int> dataset = { 9, 1, 2, 7, 5, 4, 8, 6, 3 };
    Timer timer;
    
    DS::FixedSizeArray fixedSizeArray(dataset.data());
    DS::DynamicSizeArray dynamicSizeArray(dataset.data());
    DS::LinkedList linkedList(dataset.data());
    DS::BinarySearchTree bst(dataset.data());
    
    {
        timer.start();
        for (int i = 0; i < fixedSizeArray.size(); i++)
        {
            printValue(fixedSizeArray[i]);
        }
        timer.stop();
    }

    {
        timer.start();
        for (int i = 0; i < dynamicSizeArray.size(); i++)
        {
            printValue(dynamicSizeArray[i]);
        }
        timer.stop();
    }


    {
        timer.start();
        auto cursor = linkedList.start();
        while (cursor != NULL)
        {
          printValue(cursor.value());
          cursor = cursor.next();
        }
        timer.stop();
    }

    {
        timer.start();
        bst.traverse(printValue);
        timer.stop(); 
    }

    // additional structures coming in...
}
```

Well, it doesn't look beautiful :(

Even though we have only one test dataset, we have to write lots of *container specific* functions to visit each element. 

If you thought it already smells like a hell to be refactored, yes you are on the right track.

We use **Iterator Pattern** here to make them consolidate.

## What Iterator Pattern is trying to solve?

- Open/Closed Principle
  - Introducing your new type of container can support Iterator Pattern clearly and easily. Switching the existing container is zero cost.
- **Same enforced interfaces, among any types of container**
  - It means that you can hide any complex details of a container's implementation while providing concise interface to access them.

But...

- You might lose specific advantages of some container
  - If you are accessing ordered data of Fixed Size array so many times but rarely update any of them, iterating with index will significantly faster at bigger size memory thanks to memory address indexing.
- As always, can be an overkill if you'd never change the container type.
- It may differ depends on implementation or language specific. At least in C++, iterator gives you the *reference of the element from container*, *not from the original data*. And it has its own cursor to browse. It means if you keep the reference of iterator's result, there is a potential bug that you will create.

  ```c++
  #include <vector>
  #include <iostream>

  int main(void)
  {
      std::vector<int> l = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

      // Have a pointer of the element at 5th, which is 5.
      // YOU MUST NOT WRITE THIS KIND OF EVIL CODE!
      int& target = &(l.begin() + 4);

      std::cout << "Before removal : " << target << std::endl;

      // Remove 3rd element
      l.erase(l.begin() + 2);

      std::cout << "After removal : " << target << std::endl;
      return 0;
  }
  ```

  Result of targets are 

  ```
  Before removal : 5
  After removal : 6
  ```

  Cursor is still pointing at 5th element of the container. But if you just glance the code, it doesn't seem very logical because you would think *target* is an element reference of 5th. What if the cursor was pointing at the last element? It is segmentation fault now.

## Keep in mind

Even though the Iterator Pattern solves flexibility and portability, there is always an edge case that you might not want to use Iterator as we just discussed above.

Mostly that is because you are trying to leverage characteristics, powers of a specific container.

There are two types of iterator.

* Active Iterator (External Iterator)
  - Iterators that have access to each element, control states (go back and forth), or even remove them.

* Passive Iterator (Internal Iterator)
  - Iterators that only can look and grab the data inside.
  - You can find them in functional programming concepts with lambda
    - ex) map, filter, sum functions
      ```ts
      let arr = [2, 5, 6, 3, 8, 9];
      var newArr = arr.map((val, index) => {
        console.log("Key: ", index, ", Value: ", val);
        return val * val;
      });

      console.log(newArr);
      ```
      
      ```
      [LOG]: "Key: ",  0,  ", Value: ",  2 
      [LOG]: "Key: ",  1,  ", Value: ",  5 
      [LOG]: "Key: ",  2,  ", Value: ",  6 
      [LOG]: "Key: ",  3,  ", Value: ",  3 
      [LOG]: "Key: ",  4,  ", Value: ",  8 
      [LOG]: "Key: ",  5,  ", Value: ",  9 
      [LOG]: [4, 25, 36, 9, 64, 81] 
      ```

## Code Example

Iterator Pattern is a very common concept we can find in lots of languages. So I would share some other languages' iterators.

* **C++**

  As you can see from here, C++'s For-Each iterator syntax is actually using existing iterator, but passively. [Reference](https://en.cppreference.com/w/cpp/language/range-for)

  ```cpp
  auto && __range = range-expression ;
  for (auto __begin = begin-expr, __end = end-expr; __begin != __end; ++__begin)
  {
      range-declaration = *__begin;
      loop-statement
  }
  ```

* **Python**
  
  Python so easy! Thanks to enumerate, zip, and many other functions it is very convenient to customize your iterations.

  ```py
  xs = [1, 2, 3, 4, 5, 6, 7, 8]

  # Typical iterator
  for x in xs:
      print(x)

  # Get index and the element at the sametime
  for idx, x in enumerate(xs):
      print(idx, x)
  ```

* **Rust**
  
  In Rust, since the language design stricts mutation of the elements unless it is needed, it supports three variations. [Reference](https://doc.rust-lang.org/rust-by-example/flow_control/for.html)

  ```rust
  let names = vec!["Haven", "Ken", "Juan"];

  // 1. Normal iterator
  for name in names.iter() {
      match name {
          &"Haven" => println!("There is a raacker among us!"),
          _ => println!("Hello {}", name),
      }
  }
  println!("names: {:?}", names);
  // Hello Haven
  // Hello Ken
  // There is a raacker among us!
  // names: ["Haven", "Ken", "Juan"]

  // 2. move the list into the loop and it is no longer available onward.
  for name in names.into_iter() {
      match name {
          &"Haven" => println!("There is a raacker among us!"),
          _ => println!("Hello {}", name),
      }
  }
  // Compile Error!
  //println!("names: {:?}", names);


  let mut names = vec!["Haven", "Ken", "Juan"];

  // 3. Let you mutate the list through iterator
  for name in names.iter_mut() {
      *name = match name {
          &mut "Haven" => println!("There is a raacker among us!"),
          _ => "Hello",
      }
  }

  println!("names: {:?}", names);
  //names: ["There is a raacker among us!", "Hello", "Hello"]
  ```

## Example Ideas

- Post officer

  As we discussed above, Post Officer's visits will be under his/her own order. It can be the shortest path, longest path to kill some time, or visit A&W burger for a lunch on the way. They don't care about what the parcels are. Just visiting each house to get the job done is only their concern.

- Notification History

  It is more like a sort of stack but it can provide back and forth traverse option to retrieve notifications from previous.

- Playlist player

  When you start listening a playlist on Spotify, it will start playing from the first song of the list. If the shuffle is on, it will randomize songs in the queue. 