---
title: "Swift Note : Types - Optional"
last_modified_at: 2022-04-25T11:54:00-08:00
categories:
    - iOS
tags:
    - [Swift, iOS, Study Note Series, Intermediate Level]
excerpt: "Optional is a golden key of the Swift Language and is that how we make programs type-safe. Understanding Optional deeply means writing a stable and better program."
toc: true
---

Swift is a type-safe language. We already saw lots of type-safe languages and they are trying different approaches.

[Wikipedia - Type safety](https://en.wikipedia.org/wiki/Type_safety)

>In computer science, type safety is the extent to which a programming language discourages or prevents type errors. ... Type enforcement can be static, catching potential errors at compile time, or dynamic, associating type information with values at run-time and consulting them as needed to detect imminent errors, or a combination of both. Dynamic type enforcement essentially allows an invalid program to run. 

In Swift, we have a tool called *Optional* to control compile time type checking and runtime type checking.

Runtime or dynamic time type checking is not an easy job. Because once the compilation has finished, you don't know how the program will behave at certain edge cases. That is why we are having type errors, runtime crashes, etc.

But by using Optionals, in a concise and an appropriate way, we can prevent those issues and design, structure the program very safely.

We will not cover static type check in this post. Except type inferencing & weak-type languages such as java script, you cannot assign String value to an integer variable anyway. 

## Other type-safe language example

Let me briefly bring C++ snippet in here. It should be straightforward even though you don't know C++.

```c++
class SomeClass
{
public:
    void printMyName()
    {
        std::cout << "I am a new born class" << std::endl;        
    }
}

SomeClass* createNewClass()
{
    return new SomeClass();
}

int main()
{
    // Generate SomeClass instance
    SomeClass* createdClass = createNewClass();

    // Access instance method
    createdClass->printMyName();

    // Deallocate the memory
    delete createdClass;
}
// I am a new born class
```

From the above example, we are creating a new instance of SomeClass and calling its instance method, printMyName.
But what if... you didn't properly called the createNewClass()?

```c++

// We didn't handle successful variable properly!
bool successful = false;

SomeClass* createNewClass()
{
    //...
    if (successful) {
        return new SomeClass();
    }

     // If you check NULL directly, you will have runtime error still since
     // C++ will not initialize pointers automatically,
     // because of performance and language design reason.
    return NULL;
}

int main()
{
    SomeClass* createdClass = createNewClass();
    createdClass->printMyName();

    delete createdClass;
}
// Access violation reading location
```

You are trying to access the unallocated memory block because *createdClass* variable will have a garbage value.

For the most of cases to avoid this issue, we usually check the type before we use it if the NULL check is needed.

```c++
int main()
{
    SomeClass* createdClass = createNewClass(); 

    if (createdClass != NULL)
    {
        createdClass->printMyName();

        delete createdClass;
    }
}
// Nothing happens...
```

Yes, we checked the type of createdClass manually and if it's NULL, we are not doing any instance related actions. But this issue is happening because we don't know what is going to happen. The engineers have their own responsibility to check types and control them wherever it is required to make the program safe in runtime. And because of that, since we are all human-being, we make mistakes or face uncertain crashes because of program misbehavior or logic errors. 


## Optional and nil

[Swift Document](https://docs.swift.org/swift-book/LanguageGuide/TheBasics.html#ID330)

Swift's approach is to make sure the variable can be null or not in compile time and in the code by using Optional Keyword, *?*. 

And in Swift, we use *nil* to express null or non-exist data.

```swift
var possibleName: String?
print (possibleName)
// nil

var forcedName: String
print (forcedName)
// error: Variable 'forcedName' used before being initialized

forcedName = nil
// error: 'nil' cannot be assigned to type 'String'
```

possibleName is a variable that **can** contain String type. Which means there is a chance that this variable do not have a value as you can see from the above snippet.

But if you do not define it as Optional, accessing variable without initialization is prohibited at compile time because it is defined as non-optional and that means! it cannot have a chance that it will not have a value, never ever ever. Thus, you even cannot assign nil to non-optional variables.

In summary, *If a variable or a constant is not an optional, it **MUST** have a value always. No exception.*

Because of that **MUST** constraint, we can make sure the value will have no chance to be nil in our code. And **only if** when the variable has a chance to be nil, we define it as an optional and provide extra checks to control nil checks.

That is the reason why we can call Swift as a type-safe language.

Well but still, if you are using Optionals everywhere even though it is not needed, you are not leveraging Swift's power into your program and make it fragile. So you should be careful and think twice when you are adding that small question mark right after a type.

## Optional behind the scene

```swift
var possibleName: String?
print (type(of:possibleName))
// Optional<String>
```

If you define an Optional typed variable, the dynamic type result is going to be **Optional\<TypeName\>**.

Behind the scene, Optional is defined as a generic enumeration. [Swift github](https://github.com/apple/swift/blob/main/stdlib/public/core/Optional.swift)

```swift
public enum Optional<Wrapped>: ExpressibleByNilLiteral {
    case none
    // "some" can contain associated value
    case some(Wrapped)

    public init(_ some: Wrapped) {
        self = .some(some)
    }

    public init(nilLiteral: ()) {
        self = .none
    }
}
```

Using **Associated Value** of Enumeration, it stores the Wrapped type value in **.some** and if it is nil, it will have **.none**

And we can access those enum values as well.

```swift
let age: Int? = 20

switch age {
    case .none:
        print("No age information")
    case .some(let x) where x < 20:
        print ("teenager")
    case .some(let x) where x < 65:
        print ("adult")
    default:
        print("elder")
}
```
<br/>

## Optional Chaining

[Swift Document](https://docs.swift.org/swift-book/LanguageGuide/OptionalChaining.html)

Now we know what is Optional. Then how can we retrieve stored values of Optionals and use them? There are two ways, **Optional Chaining** and **Optional Binding**

If you have an Optional variable, add question mark to call methods or access properties.

```swift
class SomeClass {
    func foo() {
        print ("Fooooo")
    }
}

var someClass: SomeClass? = SomeClass()
someClass?.foo()
// Fooooo
```

It is a special syntax that only runs when the optional has a value. If it doesn't it will not do any actions.

It's pretty handy but I think you already can see the limitation. The unwrapped value can be used only one time at the line of code and you cannot handle behaviors when the value is nil. 
<br/>

## Optional Binding

I think this is the most used and beloved syntax for me. It makes using Optionals easier and also you don't have to use Optional chainings once you retrieve an unwrapped value.

There is two options. **if let** and **guard let**

```swift
func printMyAge(age: Int?) {
    if let myAge = age {
        print ("My age is \(myAge)")
    } else {
        print ("I don't have age...?")
    }
}

// or...
func printMyAge(age: Int?) {
    // You can use the same name to hide original Optional.
    // Not highly recommended but you will find it useful sometimes.
    guard let age = age else {
        print ("I don't have age...?")
        return
    }

    print ("My age is \(age)")
}
```

***if let*** keeps the variable scope inside of your if statement but ***guard let*** will expose the unwrapped value outside of the scope and also you must define *else statement* to handle behaviors or error checking of nullity.

This could be your preference, but in my opinion, reducing indentations is always a better choice if it is applicable. Which means guard is preffered for me. But here is a good reading to check out.

>Use **if let** when the non-nil case is valid. Use guard when the nil case **represents some sort of error.** *- BallpointBen*
[Stackover flow - if let VS guard let](https://stackoverflow.com/questions/32256834/swift-guard-let-vs-if-let)

I agree with BallpointBen's idea. If the nil case will not cause any issue, ***if let*** is good to go. 

But if the code must check the nil case and the value shouldn't be nil furtherdown, use ***guard let*** for a better logic and readability of your code.

```swift
func fetchData(url urlString: String) {
    guard let url = URL(string: urlString) else {
        print ("Cannot create URL Object")
        return
    }
    
    let session = URLSession(configuration: .default)
    let task = session.dataTask(with: url) { (data, response, error) in
        if let e = error {
            print ("Failed to fetch data from the url \(urlString)")
            return
        }
        
        guard let data = data else {
            print ("Wrong data")
            return
        }
        
        do {
            // ...
        } catch {
            print (error)
        }
    }
    task.resume()
}

// or...

func fetchData(url urlString: String) {
    if let url = URL(string: urlString) {
        let session = URLSession(configuration: .default)
        let task = session.dataTask(with: url) { (data, response, error) in
            if let e = error {
                print ("Failed to fetch data from the url \(urlString)")
                return
            }
            
            if let data = data {
                do {
                    // ...
                } catch {
                    print (error)
                }
            } else {
                print ("Wrong data")
                return    
            }
        }
        task.resume()
    } else {
        print ("Cannot create URL Object")
    }
}
```

This is a snippet of fetching URL in swift code. Well... which one you prefer more? I'm very biased to the first one.
<br/>

## Nil Coalescing Operator

It is also a *quality of life* syntax to help you out dealing with nil cases.

Nil Coalescing Operator will help you with initializing unwrapped value to a default value if it is nil.

```swift
let myOptional: String? = nil

let unwrappedOptional: String = myOptional ?? "No Value" //Default value
```

if myOptional has a value, it will return the value to unwrappedOptional but since it has nil, unwrappedOptional takes "No Value"

```swift
//...
public func ?? <T>(optional: T?, defaultValue: @autoclosure () throws -> T)
    rethrows -> T {
    switch optional {
    case .some(let value):
        return value
    case .none:
        return try defaultValue()
    }
}
```

As you can see from the ?? function definition, if it is nil, it will try to return the defaultValue you passed to the function.
<br/>

## Implicitly Unwrapped Optionals or IUO

[Swift Document](https://docs.swift.org/swift-book/LanguageGuide/TheBasics.html#ID330)

I didn't introduce the exclamation point "!" for Optionals. It is a special operator for Optional which does forced unwrapping of your optional value.

```swift
let iAmOptional: String? = "Yes, I am optional"
let storeOptionalValue: String = iAmOptional!

if iAmOptional != nil {
    print (#"I know I have a correct value of "\#(iAmOptional!)""#)
} else {
    print ("No... I don't have.")
}
// I know I have a correct value of "Yes, I am optional"
```

Optionals are useful for checking nullity and making program safe in runtime but when you are *very sure* that the Optionals have values, you can unwrap the value directly without Optional binding.

Meanwhile, ***Implicitly Unwrapped Optional*** is a different form of Optional that have an extra feature.

```swift
let iAmOptional: String! = "Yes, I am optional still"

// an exclamation point is not needed
let forceUnwrapped: String = iAmOptional
```

It is more like *giving a permission for Optionals to force unwrap the value when it is needed.*

> When you use an implicitly unwrapped optional value, Swift **first tries to use it as an ordinary optional value**; if it can’t be used as an optional, Swift force-unwraps the value. - Official Document.

It is a handful form of Optional that you don't have to care about unwrapping, chaining or checking Optional value if you are sure that Optional will have a value in runtime.

```swift
let iAmOptional: String! = nil
let anotherOptional = iAmOptional
print (type(of:anotherOptional))
// Optional<String>
```

Type of anotherOptional has inferenced as normal Optional since it is applicable.

But implicitly unwrapped optional is still an Optional. It can store nil and it will try force-unwrapping if it cannot be used as an optional.

```swift
let iAmOptional: String! = nil
let forceUnwrapped: String = iAmOptional
// No compile error

print (forceUnwrapped)
// Runtime Error!!!
```

Then why do we need this? It's more close to putting your program into danger isn't it? Yes, it is. If you are unsure about the lifetime of the optional, you should not use it.

But tbh, you are already using it bunch.

```swift
class ViewController: UIViewController {
    @IBOutlet weak var titleLabel: UILabel!
    //...
}
```

If you are using Storyboard when doing a UI layout in iOS, you've already seen these implicitly unwrapped optionals lots of time. Because they are linked to the Storyboard by Storyboard outlet, if you were able to compile the iOS project, it means the outlet has connected to the component clearly.

In other words, you are guaranteed that the UIView exists 100%. That's why the linked UIView from your storyboard will have exclamation point.

And by doing that, you don't need to guess your value exists or not everytime when you are using it.

```swift
// Question mark is not needed.
titleLabel.text = "How do you like your eggs?"
```
<br/>

Optionals are the core essential of Swift along with Protocols and other key features. Understanding Optionals properly and leveraging its power is going to be a strong trait as an iOS developer.