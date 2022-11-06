---
title: "React Note - 1. Basics"
last_modified_at: 2022-10-30T00:10:00-08:00
categories:
    - React
tags:
    - [react, frontend]
excerpt: "React JS is being a dominant UI framework"
toc: true
---

## What is React

[reactjs](https://reactjs.org/) is a JavaScript **Library** for building **user interfaces**

* Declarative
    - Like the other UI frameworks such as flutter or SwiftUI, Declarative API makes the code easy to understand and highly maintainable.
* Component-Based
    - Everything is JavaScript and encapsulated components. They are simple, sometimes stateful, efficiently update where it is needed.
* Learn Once, Write Anywhere
    - Dependency free and get well along with existing Javascript which makes it easy to turn over and port into it.


## React.js and ReactDOM.js

ReactJS is the Engine code, makes the script interactive.

[ReactDOM(React Document Object Model)](https://reactjs.org/docs/react-dom.html) lets you put React Elements inside of HTML file.

> The react-dom package provides DOM-specific methods that can be used at the top level of your app and as an escape hatch to get outside the React model if you need to.

### How to import React using CDN Link
```js
<!DOCTYPE html>
<html>
    <body>
    </body>
    <script crossorigin src="https://unpkg.com/react@18/umd/react.development.js"></script>
    <script crossorigin src="https://unpkg.com/react-dom@18/umd/react-dom.development.js"></script>

    <script>
        
    </script>
</html>
</html>
```

## React has seamless syntax for React Elements

It is called [**JSX (React Syntax Extension)**](https://reactjs.org/docs/introducing-jsx.html)

JSX is not a mandatory for using React but it is very effective way of describing UI Elements in react components.

**Babel** convert JSX into *createElement* code

```js
const Title = React.createElement("h3", {
    onMouseEnter: () => {
        console.log("I'm on hover");  
    },
    onMouseLeave: () => {
        console.log("I'm leaving");
    },
}, "Hey I'm span");
const NewButton = React.createElement("button", {
    onClick: () => {
        console.log("I got clicked");
    },
}, "Click Me")
```

this code turns into

```js
const Title = () => (
    <h3 onMouseEnter={console.log("I'm on hover")}
        onMouseLeave={console.log("I'm leaving")}>
        Hey I'm Span
    </h3>);
const NewButton = () => (
    <button onClick={console.log("I got clicked")}>
        Click me
    </button>);
```

* Each component should start with **Upper Case** since html tags or any reserved keywords start with lower case

```js
// This is not gonna work.
<label for="minute_input">Minutes</label>
<input id="minute_input" placeholder="Minutes" type="number" />

<label htmlFor="minute_input">Minutes</label>
<input id="minute_input" placeholder="Minutes" type="number" />
```

## React only concerns about what has been changed

React will update only the update-required component.

When the state gets changed, **component will be re-rendered** but *reuse the existing reusable components*.

In more formal meaning, this is the React's *Render-Commit* mechanism built on top of Virtual DOM system.

Will cover about the Virtual DOM [in the next post](https://raacker.github.io/react/react-note-virtual-dom/).