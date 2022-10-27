---
title: "Swift Note : Structures and Classes"
last_modified_at: 2022-04-27T00:10:00-08:00
categories:
    - iOS
tags:
    - [Swift, iOS, Study Note Series, Intermediate Level]
excerpt: "Structures and Classes are another core essential portion of Swift along with Optionals. Even though they are the concepts have been existing over decades, Swift has a slight different approach you might want to check out."
toc: true
---

[Swift Document](https://docs.swift.org/swift-book/LanguageGuide/ClassesAndStructures.html)

Just a quick note here. Keep your eye on the url of above link and the title of that document. Seems a bit different isn't it?

ClassesAndStructures in URL / Structures and Classes in title? Did Apple change their mind after writing up the documents? Are the Structures more important now? 

You will find the reason in this Study note post.


## Structures

From my standpoint, C was the only language that I didn't have class concept. Structures are in everywhere, Classes are also in most of languages(except some OG languages :p) you would ever learn, even in Javascript now. 

**Structure** itself is a container that holds multiple properties and by doing that, it creates **a newly defined complex data type**.

```swift
var imageWidth: Int = 1920
var imageHeight: Int = 1080
var bitsPerPixel: Int = 24

struct Image {
    var width: Int
    var height: Int
    var bits: Int
}
```

If you define every properties as individual variables, the code cannot show a relationship of the data and it makes hard to read and maintain the code.

But as we did at above snippet, we created a structure called ImageResolution and it is now a new special data type that can express resolution of an image.

Now we define functions to use the new data type.

```swift
func calculateImageSize(resolution: ImageResolution) -> Int {
    return resolution.width * resolution.height * resolution.bits
}
```

This is a common usage of structure in lots of languages. But what if you need to provide 10 different functions that are commonly used for the structure? They are very coupled to the structure and fall very useless without it.

Lots of modern languages including Swift are providing an improved Structure concept that it can contain methods, initializers, etc.

```swift
import Foundation

struct Vector3d: CustomStringConvertible {
    var x: Double
    var y: Double
    var z: Double
    
    var description: String {
        return "\(x), \(y), \(z)"
    }
    
    init (_ x: Double, _ y: Double, _ z: Double) {
        self.x = x
        self.y = y
        self.z = z
    }
    
    func dot(_ v: Vector3d) -> Double {
        return x * v.x + y * v.y + z * v.z
    }
    
    func cross(_ v: Vector3d) -> Vector3d {
        return Vector3d(y * v.z - z * v.y,
                        z * v.x - x * v.z,
                        x * v.y - y * v.x)
    }
    
    func squaredNorm() -> Double {
        return dot(self)
    }
    
    func length() -> Double {
        return sqrt(squaredNorm())
    }
}

extension Vector3d {
    static func -(lhs: Vector3d, rhs: Vector3d) -> Vector3d {
        return Vector3d(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z)
    }
    static func +(lhs: Vector3d, rhs: Vector3d) -> Vector3d {
        return Vector3d(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z)
    }
    static func /(lhs: Vector3d, c: Double) -> Vector3d {
        return Vector3d(lhs.x / c, lhs.y / c, lhs.z / c)
    }
    static func *(lhs: Vector3d, c: Double) -> Vector3d {
        return Vector3d(lhs.x * c, lhs.y * c, lhs.z * c)
    }
    func normalized() -> Vector3d {
        return self / self.length()
    }
}

var v1 = Vector3d(1.0, 2.0, 3.0)
var v2 = Vector3d(1.0, 5.0, 7.0)

print (v1.dot(v2))
// 32.0
print (v1.cross(v2))
// -1.0, -4.0, 3.0
print (v1.length())
// 3.7416573867739413

var v3 = v1 - v2
print (v1 - v2)
// 0.0, -3.0, -4.0

print (v1.normalized())
// 0.2672612419124244, 0.5345224838248488, 0.8017837257372732
```

I know the code went very very far. At least I didn't use generic... But I'm sure you can remind the reason why we've been having methods in Structures.

## Classes

Classes, on the other hand... Wait. No, there is no "on the other hand".

In Swift, since Swift's Structures have lots of advanced features, Classes and Structures share lots in common.

You can imagine Classes contains Structures. Everything you can do with Structures, you can do it with Classes. We even can convert the above Vector3d implementation into class by changing **struct** keyword to **class**.  
<br/>

## Then... What is the differences?

Remember these only.

1) ***Structures are value type.***

When you pass, assign them to somewhere, it will always create a new structure by copying data as we do with Integer, String or Double.

There is a way to pass it as reference without copying (in-out) but it is originally a new data type as I described above and it will be always copied to others.

```swift
var v1 = Vector3d(1.0, 2.0, 3.0)

// v2 is a totally new Vector3d
var v2 = v1
v2.x = 0.0

print(v1)
// 1.0, 2.0, 3.0

print(v2)
// 0.0, 2.0, 3.0

func address(o: UnsafePointer<Void>) -> Int {
    return unsafeBitCast(o, to: Int.self)
}

print(NSString(format: "%p", address(o: &v1)))
// 0x10521c2a0

print(NSString(format: "%p", address(o: &v2)))
// 0x10521c2b8
```

v2.x change didn't apply to v1. v1 and v2 have totally different struct because it had been copied to v2.

And also address of both structures are different as well. Kinda obvious right?

0xB8 - 0xA0 is 24 bytes which is 3 doubles. Yes. v2 has allocated a new memory.
<br/>

2) ***Classes are reference type.***

As we usually use classes in other languages, Swift's Classes are also reference types. When we pass a class to somewhere, it won't copy but pass the reference (memory address) of the class. In this context, that memory address means the memory of class's instantiated instance.

```swift
// Let's say we changed Vector3d to be class
var v1 = Vector3d(1.0, 2.0, 3.0)

// v2 is also a reference variable that holds v1's instance
var v2 = v1
v2.x = 0.0

print(v1)
//0.0, 2.0, 3.0

print(v2)
// 0.0, 2.0, 3.0

func address(o: UnsafePointer<Void>) -> Int {
    return unsafeBitCast(o, to: Int.self)
}

print(NSString(format: "%p", address(o: &v1)))
// 0x1041783e0

print(NSString(format: "%p", address(o: &v2)))
// 0x1041783e8
```

v2 is allocated at + 0x8 of v1 which means the each reference variables' size is 8 bytes in 64 bits system and v1 and v2 are yet address container and they don't have the actual value.
<br/>

3) Classes have extra features such as inheritance, polymorphism but not Structures.
<br/>

## Features they share and don't share

[Swift Document](https://docs.swift.org/swift-book/LanguageGuide/ClassesAndStructures.html#ID83)

Share...

- Properties
- Methods
- Subscripts
- Initializer
- Have extra adapters from Extensions
- Conform to Protocol

And these are class only.

- Inheritance
- Polymorphism using type casting
- Deinitializer
- Reference Cycles 
<br/>

## Properties
[Swift Document](https://docs.swift.org/swift-book/LanguageGuide/Properties.html)

Variables or Constants that represent data of structures or classes.

- Stored Properties (instance variables)

- Computed Properties
    You can define 