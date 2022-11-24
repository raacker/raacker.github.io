---
title: "TMIOS Design Pattern, 18 - Memento"
last_modified_at: 2022-11-23T23:39:00-08:00
categories:
    - designpattern
tags:
    - [Design Pattern, TMIOS]
excerpt: "Teach me in one sentence, Design Pattern series - Memento"
toc: true
---

> GoF Numbering : 18<br/>
> Category : Behavioral Pattern<br/>
> Readings : [Wikipedia](https://en.wikipedia.org/wiki/Memento_pattern),
[cs.unc.edu](https://www.cs.unc.edu/~stotts/GOF/hires/pat5ffso.htm),
[Refactoring.guru](https://refactoring.guru/design-patterns/memento)<br/>
> As known as : Snapshot

## In One Sentence

Hänsel and Gretel's bread scrums that helps you go back to where you were at.

> All the bread scrums were gone because of birds but let's just say it is still there. Hänsel and Gretel can track them back to see where the location was.

![hansel_and_gretel_states](/_posts/design-pattern/18-Memento/images/hansel_and_gretel.png)

<sub>Image by [AlyssaTallent](https://storiestogrowby.org/story/hansel-and-gretel-bedtime-stories-for-kids/)</sub>

## Problem

The easiest case to think about is **Undo** operation.

When you are using [Command Pattern](https://raacker.github.io/designpattern/tmios-14-command/), the advantage you could get from using it is "Undo & Redo" feature.

Since you have a history of each command, you can track back operations of the command to un-apply. Then, you need to remember what happened to the object after and before the command (using timestone 🙄).

At this point, **Memento Pattern** exactly acts as a *Snapshot*. Store affected values of the object and retrieve them when undoing.

Well sadly, our *actual problem* joins the game now. Here is why.

In our real life development, most of data objects (or classes) contain very important information and **we don't want them to be exposed externally**. Why "Exposing members" deserves hatred?

Compiler will let you expose them, no problem. But it creates so much coupling overall and the logic & pipeline of the program goes *unexpected*. Because no one cares which value goes in, what methods can be used or not, etc. It is a total mayhem!

*Getter and Setter*, *Access modifiers (private, protected, etc.)* are introduced to defeat this monster. They fight really well by restricting access of own members. They draw boundaries that others cannot across. And eventually if the data or method belongs to its own, no one can touch it. Perfect.

No.

We have different problem now because of this restriction.

When we want to take a snapshot of an object, it means we have to store most of, basically all of, members. Especially, as I mentioned above, most of private members are very critical information of an object. We need to store them for sure. But most of modern software design uses lots of design patterns and mostly they ensure you have abtraction layers at some point.

In other words, You don't have any acknowledgement or access inside of an object. It is kind of trade off we made. We got huge flexibilty, modularity, maintainability (which are the most important factors in Software Design though) but we lose access to "**Detailed** control over data".

## What Memento Pattern is trying to solve?

**Memento Pattern** doesn't act only for storing intermediate data. It has an important role to secure encapsulation of objects and let them unrevealed even though we need some access to their very hidden deep informations.

In formal words, Memento Object works with the **Owner Object(or Originator)** closely and it has an access to private fields of the owner. The Originator can store Memento Objects as many as it wants(as a history of states). When a desired state is required, it retrieves a Memento Object and rollback all the fields.

If we don't use Memento Pattern for storing states, we *have to* modify the accessor or find something very ~~shitty~~ bad solution.

## Keep in mind

Memento Pattern could be language-specific pattern when it comes to immutability and integrity of a Memento Object.

Nested Class or Friend Class will work very well as a Memento Object but we must ensure they cannot be changed overtime. But some of dynamic languages such as php, javascript will not assure when they get changes.

And someone should take care of the history, mostly the Originator. But it means the external controller (so called caretaker or controller) doesn't know the existence of leftover states. Since each Memento Object tends to be a memory object, it could lead a memory leak if their life cycles are not managed properly.

## Code Example

[Conceptual C++ Version](https://github.com/raacker/raacker.github.io/tree/master/_posts/design-pattern/18-Mememto/codes/cpp)

The conceptual C++ Version demonstrates simple concept of storing states and retrieving them back using Serialization library.

As you can see from the code, states are managed by Originator itself and the memento is accessing its private member value to store.

> Disclaimer : Yes, this example is yet perfect. But the ideal and real-life solutions will be serializing, in most of cases. And friend class keyword will be another which is only C++/C# feature though.
>
> In this Conceptual example, I used *Introduce Parameter Object* from Refactoring and *alpaca library* to accept struct as a parameter.

## Example Ideas

- OS Reset System
  - As you can see from Window's recovery system, they keep a snapshot of the OS before some specific events or big changes. You can select the backup time and use the backup information to rollback.

- Server Client Snapshot
  - Very similar concept as above example. But I think it's more common to think about nowadays since most of cloud based computing instances support backup and recovery system.

- Text File Editor
  - Very common idea to think about when it comes to *undo* command.
