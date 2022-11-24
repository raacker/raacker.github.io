---
title: "React Note - 4. Props"
last_modified_at: 2022-11-11T19:10:00-08:00
categories:
    - React
tags:
    - [react, frontend]
excerpt: "Props is an essential of reusability"
toc: true
---

## What is props

Props? Properties. 

Yes, it is nothing more than that. But it has all mighty power underneath.

## Problem

Let's simply define a Button Component to start. We will use a theme color to match with other components.

```js
const CommonButton = () => {
    return (
        <button style={{
            backgroundColor: "green",
            color: "white",
            padding: "10px 20px",
            border: 0,
            borderRadius: 7
        }}>
            Button
        </button>
    );
};

const App = () => {
    return (
        <div>
            <CommonButton />
        </div>
    );
};
```

Yes, very simple one. But I'm sure you already realized this is unusable. 

How are you going to define onClick event? How are you going to change the text inside of button tag? fontSize? 

We just matched the style of button but it is too static. Very opposite from what we are expecting to engineer.

## Here comes Props

We reinforce the <code>CommonButton</code> with props now.

```js
const CommonButton = (props) => {
    return (
        <button style={{
            backgroundColor: "green",
            color: "white",
            padding: "10px 20px",
            border: 0,
            borderRadius: 7
        }} onClick={ props.onPressed }>
            { props.label }
        </button>
    );
};
const onButtonClick = () => console.log("I got clicked");

const App = () => {
    return (
        <div>
            <CommonButton label={"Button1"} onPressed={ onButtonClick }/>
        </div>
    );
};
```

If you take parameters in Component, it will be passed as an object. And it will contain all the properties you passed into the Component.

<code><CommonButton label={"Button1"} onPressed={ onButtonClick }/></code>

Thanks to the props, we can define any buttons as much as we want.

```js
const onButton1Click = () => console.log("Button 1 got clicked");
const onButton2Click = () => console.log("Button 2 got clicked");
const onButton3Click = () => console.log("Button 3 got clicked");
const onButton4Click = () => console.log("Button 4 got clicked");

const App = () => {
    return (
        <div>
            <CommonButton label={"Button1"} onPressed={ onButton1Click }/>
            <CommonButton label={"Button2"} onPressed={ onButton2Click }/>
            <CommonButton label={"Button3"} onPressed={ onButton3Click }/>
            <CommonButton label={"Button4"} onPressed={ onButton4Click }/>
        </div>
    );
};
```

## Undefined Props

Javascript is sometimes very vunerable due to its dynamic types and undefined properties.

Without onClick event, this call is still valid.

```js
const App = () => {
    return (
        <div>
            <CommonButton label={"Button1"} />
        </div>
    );
};
```

<code>console.log(props.onPressed)</code> will return "undefined"

## PropTypes

Yes, we are prepared because this is a common mistake we all make. Especially when the code base gets complicated, it would happen to anybody.

Include [PropTypes](https://reactjs.org/docs/typechecking-with-proptypes.html) as a separate component.

>
    Note:

    React.PropTypes has moved into a different package since React v15.5. Please use the prop-types library instead.

    We provide a codemod script to automate the conversion.


```js
import PropTypes from 'prop-types';

CommonButton.propTypes = {
    label: PropTypes.string.isRequired,
    onPressed: PropTypes.func,
}
```

Feels like a TypeScript right? 

By defining types on propTypes, Component will ensure that you are passing expected type of value and also you can mark it <code>isRequired</code> to make sure the value exists.

But keep in mind. Undefined is still a valid syntax and propTypes cannot block you from moving on. It will just give you the WARNING message. That's all it can do.

```js
const App = () => {
    return (
        <div>
            <CommonButton />
        </div>
    );
};
```

>Warning: Failed prop type: The prop `label` is marked as required in `CommonButton`, but its value is `undefined`.
CommonButton@file:///Users/haven/Desktop/index_props.html line 14 > injectedScript:4:3
App

## Unwrapping props

How we defined props in `CommonButton` is convenient but is a bad practice because it has no meaning and nothing about required properties.

```js
const CommonButton = (props) => {
    return (
        <button style={{
            backgroundColor: "green",
            color: "white",
            padding: "10px 20px",
            border: 0,
            borderRadius: 7
        }} onClick={ props.onPressed }>
            { props.label }
        </button>
    );
};
```

Rather, we can unwrap the props object by redefining as

```js
// Order of properties doesn't matter because it is still a normal javascript Key-Value object.
const CommonButton = ({ onPressed=null, label="placeholder" }) => {
    return (
        <button style={{
            backgroundColor: "green",
            color: "white",
            padding: "10px 20px",
            border: 0,
            borderRadius: 7
        }} onClick={ onPressed }>
            { label }
        </button>
    );
};
```

You even can define default properties in case of they don't exist.