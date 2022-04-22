---
title: "Swift Note - Types Part 1"
last_modified_at: 2022-04-21T23:20:00-08:00
categories:
    - iOS
tags:
    - [Swift, iOS, Study Note]
excerpt: "Types are very basics of Swift but they are the most important concepts that you need make sure you deeply understand them"
toc: true
---

Types. If you have studied any programming languages before, the first thing you do after "Hello, World!" is declaring variables to store numbers.

Types are very basics but they are the core fundamentals of programming languages and we even have lots of problems and bugs just because of types (look at Javascript and Typescript). And even on the [Swift's introductory document](https://docs.swift.org/swift-book/LanguageGuide/TheBasics.html), it says Swift is a "type-safe" language.

This note will take steps into Swift's types and all the details need to be covered for Swift Noobs like me but who have experiences in other languages.

## 1. Primitive Types

So basics right?

* Int
    - Decimal signed integer. Defined as **64 bits** in 64-bit Machines and **32 bits** in 32-bit Machines
    - For explicitly specified sizes, you can use Int8, Int16, Int32, Int64. There is no **Short** type!
    - You can use **underscore** for a better text representation
        - 1_000_000, 1_000_000.000_000
    - For numeric literals, use 0b (binary), 0o (octal) and 0x (hexadecimal)

* Double
    - 64-bit Floating-Point Value

* Float
    - 32-bit Floating-Point Value

* Bool
    - Boolean Value

* String
    - Textural Data

* Character
    - Single Textural Value

```swift
let catCharacters: [Character] = ["C", "a", "t", "!", "🐱"]
let catString = String(catCharacters)
```


### Keep in mind

- Default type of constant numeric symbols are Int and Double.

```swift
let intValue = 10
print (type(of:intValue))
// Int

let floatValue = 10.0
print (type(of:floatValue))
// Double
```
<br/>

- Integer types contain static value of min, max and zero. [Int Document](https://developer.apple.com/documentation/swift/int/1540171-max)

```swift
print (Int16.min)
// -32768

print (Int.max)
// 9223372036854775807
```
<br/>

- For max and min value of Float and Double, need to import Darwin and use constant values

```swift
import Darwin
print (DBL_MIN)
//2.2250738585072014e-308

print (FLT_MAX)
//3.4028235e+38
```
<br/>

- use **typealias** to redefine type symbols for a better readability of the code. It's same as typedef in C++

```swift
typealias ImageBitRate = UInt32
var imagePixel: ImageBitRate = myImage(h, w)
```
<br/>

- They are structures & Protocols! 

>All of the basic types in Swift—integers, floating-point numbers, Booleans, strings, arrays and dictionaries—are **value types**, and are **implemented as structures behind the scenes**. [Swift Document](https://docs.swift.org/swift-book/LanguageGuide/ClassesAndStructures.html#ID88)
<br/>

### Any

Any is a special type in Swift. It's pretty much simlar as "auto" but yet different under the hood.

Any refers to "any" instance of a class, structure or enumeration. It means literally "everything". If you mix multiple data type into Array, the type of array will be [Any]. But you cannot make swift to inference the type of the array though since mixed data type in a collection is not type-safe to operate lots of methods.

```swift
let intAny: Any = 1
let doubleAny: Any = 109.0

let valuesExplicitAny: [Any] = [1, 2, "Fish"]

let valuesExplicitAnyObject: [AnyObject] = [1, 2, "Fish"]
// Compile Error : type of expression is ambiguous without more context

let valuesImplicit = [1, 2, "Fish"]
// Compile Error : heterogeneous collection literal could only be inferred to '[Any]'; add explicit type annotation if this is intentional
```
<br/>

### AnyObject

AnyObject is a **protocol** that all classes implicitly conform. [Swift Document](https://developer.apple.com/documentation/swift/anyobject)

It is equivalent to **id** in Objective-C

```swift
class FloatRef {
	let value: Float
	init (_ value: Float) {
		self.value = value
	}
}

let x = FloatRef(2.3)
let y: AnyObject = x
let z: AnyObject = FloatRef.self

print (type(of:x))
print (type(of:y))
print (type(of:z))
//FloatRef
//FloatRef
//__lldb_expr_1.FloatRef
```
<br/>

That definition means AnyObject is only available for any class, class type or class-only protocols. In other words, AnyObject Protocol can be used to distinguish in between *Value types and Reference types*.

```swift
struct MyStruct {

}

let canIStoreStruct: AnyObject = MyStruct()
// error: MyPlayground.playground:1:2: error: value of type 'MyStruct' expected to be instance of class or class-constrained type
// let canI: AnyObject = MyStruct()
//                       ^~~~~~~~~~
//                                  as AnyObject
```
<br/>

AnyObject also can be used as a bridge to an Objective-C class such as NSString or NSNumber. Many value types (Primitives, Structure, Enumeration) in Swift bridge to Objective-C counterparts.

```swift
let s: AnyObject = "This is a bridged string." as NSString
print (s is NSString)
// true

let v: AnyObject = 100 as NSString
print (type(of: v))
// "__NSCFNumber"
```
<br/>

### AnyClass

Umm... it is a type of.. AnyObject.Type! [Swift Document](https://developer.apple.com/documentation/swift/anyclass)

What does this mean? we should take a look at "Metatype" first.
<br/>

### Metatype

#### What is Metatype?

Metatype is **a type** of a type. In the below code snippet, Widget is a class. Yes, you are correct. It is can be called as "type" as well. But let’s just use a deeper technical term here. [Swift Document](https://docs.swift.org/swift-book/ReferenceManual/Types.html#ID455)

When you have a class (blueprint) and assign a memory block in heap space, you call that memory “instance” of a class. 

```swift
class CustomWidget {
	static var instanceCount = 0
	init () {
		CustomWidget.instanceCount += 1
	}

	func draw() {
		print ("I am drawing!")
	}

	class func currentCount() {
	  print ("We created \(instanceCount) widgets")
  }
}

let newWidget: CustomWidget = CustomWidget()
```

“: CustomWidget” indicates newWidget is a *reference constant* which can contain CustomWidget class’s instances. It is a type of an instance.

“CustomWidget()” *instantiate* CustomWidget class’s instance.

On the code, newWidget can access draw() because it is an instance method. But it cannot access currentCount() since it is a type method. 

Okay. then could you guess which result will come out of this code?

```swift
let newWidgetType = type(of:newWidget)
```

The answer is "CustomWidget.Type", not just "CustomWidget".  What's a difference?

```swift
let newWidgetType = type(of:newWidget)
print (newWidgetType)
//__lldb_expr_1.CustomWidget.Type
```

In detail, CustomWidget class's type is CustomWidget.Type, so called Metatype.

- CustomWidget : Name of your class
- CustomWidget.Type : Type of your class 

#### So... AnyClass is

Cool! Now we have all the backgrounds to understand "typealias AnyClass = AnyObject.Type".

>AnyClass is a metatype of AnyObject

It is a type! which can contain other metatypes that "conform AnyObject Protocol" (or existential metatype).

```swift
print (type(of:AnyClass.self))
// AnyObject.Type.Protocol
```

We will cover this very soon.

Okay. Then what's the advantage of storing and using metatype in the code? Since you can declare a variable that can store metatype, this is even possible.

```swift
var myWidgets = [CustomWidget]()

func createWidget<T: CustomWidget>(of: T.Type) -> T {
    let widget = of.init()
    myWidgets.append(widget)
    print ("I just created a new widget #\(of.instanceCount - 1)")
    return widget
}

// Compile Error!
// error: MyPlayground.playground:4:1: error: constructing an object of class type 'T' with a metatype value must use a 'required' initializer
//    let widget = ofType.init()
//                 ~~~~~~ ^
```

Just pass a type that inherits CustomWidget class. Then it will create an instance and append to myWidgets array.

That code won't compile though because Subclass’s Type is a subset of Class’s Type. Which means our CustomWidget.Type is also a subset of AnyObject.Type but compiler cannot assure any children actually have “required” constructors or not. To fix the problem, you need to specify which initializer is a 100% necessary to be called and the most basic. [StackOverflow](https://stackoverflow.com/questions/32163124/why-must-constructing-an-object-of-class-type-someclass-with-a-metatype-value)

```swift
class CustomWidget {
	static var instanceCount = 0
	required init () {
		CustomWidget.instanceCount += 1
	}

	func draw() {
		print ("I am drawing!")
	}

	class func currentCount() {
	  print ("We created \(instanceCount) widgets")
  }
}
```

Now you can call createWidget().

```swift
createWidget(of: CustomWidget.Type)
//error: MyPlayground.playground:5:1: error: global function 'createWidget(of:)' requires that 'CustomWidget.Type' inherit from 'CustomWidget'
//createWidget(of: CustomWidget.Type)
// ^
```

Oops, so many errors 😅 Let's see what is wrong with the function parameter type.

```swift
func createWidget<T: CustomWidget>(of: T.Type) -> T {}
```

To access Type properties and methods, we need to get metatype “Type” value right? But even though we are saying "type" bunch of times, Metatype is yet just a type. That’s why passing CustomWidget.Type is completely wrong. Because we are just passing type, not a value of “CustomWidget.Type”

The answer is ".self"

```swift
createWidget(of: CustomWidget.self)
createWidget(of: CustomWidget.self)

//I just created a new widget #1
//I just created a new widget #2
```
<br/>

#### Static Metatype, .self

In Swift, .self is called **static metatype** or "compile time type of an instance". This code should look a lot comfortable now for you.

```swift
let myType: Int.Type = Int.self
```

We are storing Metatype value "self" in Int's Metatype constant "myType"


#### Dynamic Metatype, type(of:)

On the other hand, what you get from type(of:) function is a "dynamic type" or "runtime type" [Swift Document](https://developer.apple.com/documentation/swift/2885064-type)

```swift
let myNumberType: Any = 10

print (myNumberType.Type)
// error: MyPlayground.playground:57:14: error: value of type 'Any' has no member 'Type'
// print (myNum.Type)
//        ~~~~~ ^~~~

print (type(of:myNumberType))
// Int

print (myNumberType.self)
// 10
```

During the compilation, myNumberType is an “Any” type but due to type assignment and conversion, the runtime type is Int.
<br/>

#### Protocol's Metatype

It's time to talk about existential metatype.

Class, Structure, Enumeration, Primitive type, they all have Metatype. But Protocol’s type is a bit different though. 

```swift
protocol WidgetProtocol {}
let metatype: WidgetProtocol.Type = WidgetProtocol.self

// error: cannot convert value of type 'WidgetProtocol.Protocol' to specified type 'WidgetProtocol.Type'
// let metatype: WidgetProtocol.Type = WidgetProtocol.self
//                                     ^~~~~~~~~~~~~~~~~~~
//                                                         as! WidgetProtocol.Type
```

Error message says everything! WidgetProtocol.self is correct usage but the problem is at “WidgetProtocol.Type”.

“WidgetProtocol.Type” indicates *"I can store a metatype of which conforms WidgetProtocol”*. But at above snippet, we are trying to assign WidgetProtocol's metatype itself. That's why it is not a correct usage.

Then how can we get the actual actual metatype of the protocol? We have .Protocol keyword here.

```swift
print (type(of:WidgetProtocol.self))
// WidgetProtocol.Protocol

let metatype: WidgetProtocol.Protocol = WidgetProtocol.self
```
<br/>

#### 3 Self

Okay I think we have been saying self too many times in everywhere. Let's summarize what they are exactly.

1) self in instance (same as “this” in other languages)

```swift
class TextWidget : Widget {
	var name: String
	init () {
    self.name = "TextWidget"
  }
	
  func printMyName() {
		print (self.name)
  }
}
```
You use self when initializing or accessing instance properties.
<br/>

2) self as static metatype [Apple Document](https://developer.apple.com/documentation/uikit/uitableview/1614888-register)

```swift
let tableView = UITableView()
tableView.register(CustomCellWidget.self, forReuseIdentifier: "CustomCell")
```
If you’ve tried API fetching or board app samples, you have already had this code in your project.

Yes, register() takes cellClass: AnyClass? which is “typealias AnyClass = AnyObject.Type”! it takes metatype as an argument.
<br/>

3) Self as a Type of a current Type.

```swift
extension Vector3 {
	func normalized() -> Vector3 {
    return Vector3(self.data.x / self.length,
        self.data.y / self.length,
        self.data.z / self.length)
  }
}

extension Vector3 {
	func normalized() -> Self {
    return Self(self.data.x / self.length,
        self.data.y / self.length,
        self.data.z / self.length)
  }
}
```
Self keyword can be used as a type of “current type”. By using Self rather than actual Type name, you can define type-independent protocols.
<br/>

Further Readings<br/>
[What's .self, .Type and .Protocol? Understanding Swift Metatypes](https://swiftrocks.com/whats-type-and-self-swift-metatypes.html)
[AnyClass, Meta Type and .self](https://en.swifter.tips/self-anyclass/)



