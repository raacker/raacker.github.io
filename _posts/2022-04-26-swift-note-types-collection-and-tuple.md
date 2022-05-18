---
title: "Swift Note : Types - Collections and Tuple"
last_modified_at: 2022-04-26T00:10:00-08:00
categories:
    - iOS
tags:
    - [Swift, iOS, Study Note Series, Intermediate Level]
excerpt: "There is only two types of swift programmers, who use Collections and also who use Collections."
toc: true
---

Collections and tuple are data containers which you can find in *almost every programming languages.

Let's go straight forward.

## Tuple

[Swift Document](https://docs.swift.org/swift-book/LanguageGuide/TheBasics.html#ID329)

Tuple is a container of multiple values which is a simpler form compare to Structure.

```swift
let http404Error = (404, "Not Found")
let (statusCode, statusMessage) = http404Error

// You can omit other value using underscore
let (statusCode2, _) = http404Error
```

You even can name the individual elements in a tuple or access with index of each elements.

```swift
let http200Status = (statusCode: 200, description: "OK")

print("The status code is \(http200Status.statusCode)")
print("The status code is \(http200Status.0)")
// The status code is 200

print("The status message is \(http200Status.description)")
print("The status message is \(http200Status.1)")
// The status message is OK
```

We are going to see some tuple examples along with Collection types very soon.
<br/>

## Array

[Swift Document](https://docs.swift.org/swift-book/LanguageGuide/CollectionTypes.html#ID107)

A contiguous container that provides subscripting (or indexing in sequence).

```swift
var arrayForm1: Array<Double> = Array<Double>()
var arrayForm2: Array<Double> = [Double]()
var arrayForm3: [Double] = [Double]()
var arrayForm4: [Double] = []                  // ⭐️
var arrayForm5 = [Double]()                    // ⭐️
```

They are all the same Array of Double initialization codes. Since we have type inference in Swift, using the bottom two forms are the most useful and handy form of declaring arrays.

You can initialize arrays when declaring as well.

```swift
var arrayForm6: [Double] = [1.0, 2.0, 3.0]
var arrayForm7 = [1.0, 2.0, 3.0]
print(type(of:arrayForm7))
// Array<Double>

let arrayForm8 = ["Hello", "!", "World"]
print(type(of:arrayForm8))
// Array<String>

var arrayForm9 = [50, "!", "World"]
print(type(of:arrayForm9))
//  error: heterogeneous collection literal could only be inferred to
// '[Any]'; add explicit type annotation if this is intentional
// var arrayForm9 = [50, "!", "World"]
//                 ^~~~~~~~~~~~~~~~~~
//                                    as [Any]
```

When you are initializing arrays, it would be much easier to define the array type as you can see at the arrayForm9. Type inference can be useful, but you don't want to mess up your array type.

Well once you specify the type of array it is easy to break you code though.

You can iterate arrays using For-In loop in Swift and also subscripting

```swift
var shoppingList = ["Eggs", "Milk", "Flour", "Baking Powder", "Cheese"]

for item in shoppingList {
    print(item)
}

// or...
for i in 0..<shoppingList.count {
    print(shoppingList[i])
}

// Eggs
// Milk
// Flour
// Baking Powder
// Cheese

// or...
for (index, value) in shoppingList.enumerated() {
    print("index \(index) : \(value)")
}
//index 0 : Eggs
//index 1 : Milk
//index 2 : Flour
//index 3 : Baking Powder
//index 4 : Cheese
```

enumerated is a instance method of *EnumeratedSequence* that conforms Sequence Protocol. [Swift Document](https://developer.apple.
com/documentation/swift/array/1687832-enumerated)

By using enumerated() and tuple to unwrap the result values, you can have an index and a value at the same time.

<br/>

## Set

[Swift Document](https://docs.swift.org/swift-book/LanguageGuide/CollectionTypes.html#ID484)

A unique elements container that provides relationship functions

```swift
var setForm1: Set<Int> = Set<Int>()
var setForm2: Set<Int> = []                   // ⭐️
var setForm3: Set = ["Swfit", "Set"]          // ⭐️
```

Set shares the bracket form of Array. That's why Set doesn't have a shorten form to declare and you must say **Set** to use type inference.

You can iterate sets using For-In loop in Swift. Some other languages do not support set enumeration without separate functions. But keep in mind, Set doesn't have an order in elements and it doesn't conform *Sequence* Protocol. Even though for-in loop iterates in a certain order, that is just how it is being saved in memory and it will change randomly after a call of set method.

```swift
var favoriteGenres: Set = ["Rock", "Classical", "Hip hop"]

for genre in favoriteGenres {
    print("\(genre)")
}
// Classical
// Jazz
// Hip hop
```

You can find set operators from the [Swift Document](https://docs.swift.org/swift-book/LanguageGuide/CollectionTypes.html#ID490).
<br/>

## Dictionary

A key-value pair container for faster lookup and matching purpose.

```swift
var dictForm1: Dictionary<String, Int> = Dictionary<String, Int>()
var dictForm2: Dictionary<String, Int> = [:]
var dictForm3: [String: Int] = [:]                                   // ⭐️
var dictForm5 = ["Haven" : 28, "Timmy" : 1]                          // ⭐️
var dictForm6 = [String : Int]()                                     // ⭐️
```

You can define Key type as a first Generic type and Value type as a second Generic type.

Use tuple to access key-value pair, similarily as you do with Array's enumerated()

```swift
var airports = ["YVR": "Vancouver Yes Very Rainy", "ICN" : "Korea International Airport", "YYZ": "Toronto Pearson"]

for (airportCode, airportName) in airports {
    print("\(airportCode): \(airportName)")
}

// YVR: Vancouver Yes Very Rainy
// ICN: Korea International Airport
// YYZ: Toronto Pearson

for airportCode in airports.keys {
    print("Airport Code : \(airportCode)")
}
// Airport Code : YVR
// Airport Code : ICN
// Airport Code : YYZ
```
<br/>

## List

Bamboozled! Swift doesn't have a List Collection as a language support. I wondered but here is a [Swift forum discussion](https://forums.swift.org/t/adding-a-linkedlist-type-to-the-standard-library/32339) about it if you wonder.