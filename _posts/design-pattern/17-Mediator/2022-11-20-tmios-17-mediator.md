---
title: "TMIOS Design Pattern, 17 - Mediator"
last_modified_at: 2022-11-20T22:18:00-08:00
categories:
    - designpattern
tags:
    - [Design Pattern, TMIOS]
excerpt: "Teach me in one sentence, Design Pattern series - Mediator"
toc: true
---

> GoF Numbering : 17<br/>
> Category : Behavioral Pattern<br/>
> Readings : [Wikipedia](https://en.wikipedia.org/wiki/Mediator_pattern),
[DigitalOcean](https://www.digitalocean.com/community/tutorials/mediator-design-pattern-java),
[cs.unc.edu](https://www.cs.unc.edu/~stotts/GOF/hires/pat5efso.htm),
[Refactoring.guru](https://refactoring.guru/design-patterns/mediator)<br/>
> As known as : Moderator, Intermediary, Channel Center

## In One Sentence

A Police officer that you can ask how you can go or where you need to go.

![police_officer](/_posts/design-pattern/17-Mediator/images/police_officer.jpg)

<sub>Image by [storyset on Freepik]("https://www.freepik.com/free-vector/traffic-police-concept-illustration_32439083.htm#query=traffic%20policeman&position=4&from_view=search&track=sph")</sub>

> You need to bring your new report to the hospital. But to drive through, you must pass the intersection of the city. There is a police officer who guides you where you should go.
>
>Funny enough, sometimes they bring a report to you. You don't know who sent it but at least you know that's from the hospital.

## Problem

The problem that Mediator Pattern aims for is straighforward: Kill couplings.

If your modifications to a component affects others to be changed, it means they have coupling, whole lotta dependencies. It's not love, at all.

## What Mediator Pattern is trying to solve?

- Common Interface for sub components.
  - Obtain [Single Responsibility Principle](https://en.wikipedia.org/wiki/Single-responsibility_principle) : Each component does only their own thing.
  - Obtain [Open-Closed Principle](https://en.wikipedia.org/wiki/Open%E2%80%93closed_principle) : By putting an abstraction layer around components, adding extra components is a piece of cake.

But...

- At the end, Mediator Object controls lots of logics. And even though we are reducing coupling of each components, we sacrifice large coupling of Mediator-Components. We call it **God Object**.
  - Suggested way would be splitting Mediator Object into several small Mediators based on responsibility. And let them communicate each other as well. By putting nets around similar & related components, it increases maintainability of each Mediator Object and makes it easy to read.

  > If there is a ProjectManager, splitting responsibilities into ProjectIOManager, DocumentManager, UnitManager, LogManager, etc. will make it a lot easier to handle. They can be singletons or nested & composition objects depends on designs.

## Keep in mind

Dealing with coupling? yes, the goal is simple enough. But there is a special role of Mediator.

Unlike the other *sender & receiver* patterns such as [Chain of Responsibility](https://raacker.github.io/designpattern/tmios-13-cor/), [Command](https://raacker.github.io/designpattern/tmios-14-command/), Mediator opens *Bi-directional* communication channels for sub components.

It means that Mediator Pattern still keep the components do not know each other, they can send a request or receive a message from the Mediator Object. It abstracts everthing still. But it gives them a chance to send and receive at the same time.

Thus, sub components also have a reference of Mediator Object, or a channel to access Mediator Object depends on implementation.

Meanwhile, other patterns are *Uni-directional* relationship which they send a message to the sub components but sub components do not know the presence of Handler Object.

## Code Example

I realized I was doing too much "external" works rather than focusing on the Mediator Object 😅. Thus I will stop at the current state.

Some of the code should be refactored and for sure currently they remain undone.

But you will get ideas of

- How does the Mediator Object *communicate with sub components*
- How is the *Command Pattern* used as a manner of communication protocol
- *FactoryMethod* to create Commands.
  - Eventually, Aircrafts and extra components should also use Factory Method or Abstract Factory to generalize and give extra abstraction in between structures.

I will come back to this sample if I'm willing to put more comprehensive pattern mixture example later when I get into other patterns.

## Example Ideas

- Aircraft Control Tower
  - It manages a region of skyline, by calling the aircrafts to land or depart. They get approval requests from the planes.

- MVC Architecture
  - A controller of Model - View - Controller pattern is a mediator pattern as well. It cuts off the dependency of each data model & UI representation components. But it is able to interact with them bidirectionally.
