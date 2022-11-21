---
title: "TMIOS Design Pattern, 14 - Command"
last_modified_at: 2022-10-30T00:15:00-08:00
categories:
    - designpattern
tags:
    - [Design Pattern, TMIOS]
excerpt: "Teach me in one sentence, Design Pattern series - Command"
toc: true
---

> GoF Numbering : 14<br/>
> Category : Behavioral Pattern<br/>
> Readings : [Wikipedia](https://en.wikipedia.org/wiki/Command_pattern), 
[DigitalOcean](https://www.digitalocean.com/community/tutorials/command-design-pattern), 
[cs.unc.edu](https://www.cs.unc.edu/~stotts/GOF/hires/pat5bfso.htm),
[Refactoring.guru](https://refactoring.guru/design-patterns/command)

## In One Sentence

Turn a logic into standalone **Command(Transaction) Object** which you can toss around.

> When you modify your code in Visual Studio Code, every typing is a transaction. You can undo by *Ctrl+Z* and redo by *Ctrl+Shift+Z*. It remembers what you have changed and always track it down.

## Problem

Nevah had an amazing idea for a next-gen Photo Editor.

He did a lot of code and at the end, he finally made it work. He even implemented *Retouch brush (haven: I just wrote random thing)* feature which is so much powerful than Photoshop. What a monster.

The first user gave him a feedback. 

> I tried your brand new brush feature and I loved it! But it actually removed too much colors of my picture and they look ugly. But it says it *cannot be undone*. Now I have to restart my picture editing from scratch. WTH?

And the second user gave another heart-breaking feedback.

> The dropdown menu's brush and keyboard shortcut brush seems not the same. Dropdown menu did well but the keyboard shortcut just removed my images. What happened?

Another.

> I wanna see my edit history because it is so important to see what I have done visually. I thought that's such a basic feature.

All these problems started from here.

When he were implementing the Retouch Brush feature, he wrote the whole code inside of Dropdown GUI button at the beginning. But he forgot to refactor the function and added a keyboard shortcut to call that GUI function.

It was too late. Codebase was already messy, he couldn't reuse the feature outside of the function. Furthermore, he even cannot track feature usages because he didn't have support for that. Remember? they are all hard coded into the GUI Handle function.

Do you see the problem we want to solve?

- We want to reuse and reapply the action when it is needed.
- We want the action to be memorable.
- We want decoupled structure in between request, receiver

## What Command Pattern is trying to solve?

- Decoupled command requester and receivers
  - Obtain [Single Responsibility Principle](https://en.wikipedia.org/wiki/Single-responsibility_principle) : One command does one thing.
  - Obtain [Open-Closed Principle](https://en.wikipedia.org/wiki/Open%E2%80%93closed_principle) : Use commands like a lego block. Creating a new command is very easy and you don't have to modify existing codes.
- Treat an action as an object with states or parameters, so called *parameterized*.
  - You can reuse the action, in different places and also reverse it like nothing happened.
  - You even can introduce *delayed execution*, *batch actions*, *execute on multiple receivers*.

But

- You are introducing a quite complex layer. It may lead to expensive maintanance cost and often you cannot keep the design clean and slim due to dependency or reroute problems.

## Keep in mind

- Carefully design how you are going to initialize parameters of commands.

    > You might have noticed one missing piece of the puzzle, which is the request parameters. A GUI object might have supplied the business-layer object with some parameters. Since the command execution method doesn’t have any parameters, how would we pass the request details to the receiver? It turns out the command should be either pre-configured with this data, or capable of getting it on its own. [refactoring.guru](https://refactoring.guru/design-patterns/command)

    The common design for decoupled command is overriding  *Execute()* method which takes no parameter. Once you start adding variables or dynamical states to the Execute method, it will end up creating hugely coupled relationships and it will break Open/Closed Principle easily.

    One of the suggested alternative is **Executed Routed Event System** as introduced in [wikipedia](https://en.wikipedia.org/wiki/Command_pattern#Terminology). It combines command pattern and the event processing. As a result, there is no composition in between senders and receivers. And the queued events are being handled during Event execution phase with payloads.

- Consider how you are going to inject states.

    > States are usually a global information that you don't want to store as local variables. **Memento Pattern** could be a wise choice to make if applicable.


## Code Example - File Import & Export Program

Even though I put nevah's photo editor story, I'd rather write a *precisely describing example*, File Import and Export 😅

[C++ Version](https://github.com/raacker/raacker.github.io/tree/master/_posts/design-pattern/14-Command/codes/c%2B%2B)

Jeez, it wasn't my intention but the scale got too big just for "AppendCommand" 😂

You don't have to read most of the Document code but just see how the CommandManager cooperates with Commands and manage them in a stack. 

## Code Example - Did you find?

* Rollback command has body because there is a chance that undo is not possible for specific command.

* The example didn't demonstrate **Executed Routed Event System** but it could be simply described as ...

    ```C++
    ProjectCommandManager::ProjectCommandManager()
    {
        mCommands.clear();
    }
    ProjectCommandManager::~ProjectCommandManager()
    {
        mCommands.clear();
    }

    void ProjectCommandManager::NewCommand(Command* command)
    {
        mCommands.push_back(command);
    }

    void ProjectCommandManager::Resolve()
    {
        for (Command* command : mCommands)
        {
            command->Execute();
            delete command;
        }
        mCommands.clear();
    }
    ```

    The external code will call *Resolve()* when it is a good timing (thread-safe, memory align, etc..)

## Example Ideas

- Canvas Drawing
  
    Exactly command based for redo-undo.

- Smart Home Control

    It illustrates the concept of Batch or Macro Command which is a powerful aspect of Command Pattern. When you enter or leave you home, pre-defined Batch Command actions will be done and undone. For example, turn off the living room light, turn off tv, shut the blind.