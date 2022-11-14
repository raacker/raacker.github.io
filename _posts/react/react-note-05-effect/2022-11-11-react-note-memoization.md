---
title: "React Note - 5. Effect"
last_modified_at: 2022-11-13T22:10:00-08:00
categories:
    - React
tags:
    - [react, frontend]
excerpt: "Let React knows the component doesn't need to be updated that frequent"
toc: true
---

# React Note - Effect

## Rerendering everytime we change the state

```js
function App() {
    const [counter, setCounter] = React.useState(0);
    const onClick = () => setCounter(curr => curr + 1);
    console.log("Am I being rerendered?");
    return (
        <div>
            <h1>{ counter }</h1>
            <button onClick={onClick}>Click Me</button>
        </div>
    );
};

<div>
    <App />
</div>
```

This code will always rerun every time you click the button because the function App is a React component but what it does after all is just return a React component when it has been requested.

It means that if the component gets larger and complicated, rerendering the whole JSX will be very expensive and much harder to optimize it.

And also if we think about what the Components are going to render, there is a chance that you need to call an API as a result of a button. If you are requesting the API simultaniously, it's hopeless. Really bad design.

Then, **Effect** comes into this fight.

## useEffect

```js
import { useState, useEffect } from "react";

function App() {
    const [counter, setCounter] = useState(0);
    const onClick = () => setCounter(curr => curr + 1);

    // Only called at the first rendering
    useEffect(() => {
        console.log("Calling Global API");
    }, []);

    // Called every time `counter` changes
    useEffect(() => {
        console.log("Calling Counter API");
    }, [counter]);

    return (
        <div>
            <h1>{ counter }</h1>
            <button onClick={onClick}>Click Me</button>
        </div>
    );
};
```

![console.log](/_posts/react/react-note-05-effect/images/console.png)

It called the **Global API function** only once. And the **Counter API function** everytime we click the `Click Me` button.

> Unlike componentDidMount and componentDidUpdate, the function passed to useEffect fires after layout and paint, during a deferred event. [official docs](https://reactjs.org/docs/hooks-reference.html#useeffect)

Wait, does that render "Calling API" twice? probably you created the React app using create-react-app. And the App component is surrounded by **StrictMode**

![strict_mode](/_posts/react/react-note-05-effect/images/strict_mode.png)

[Stack overflow - My React Component is rendering twice because of Strict Mode](https://stackoverflow.com/questions/61254372/my-react-component-is-rendering-twice-because-of-strict-mode/61897567#61897567)

```js
import React from 'react';
import ReactDOM from 'react-dom/client';
import App from './App';

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <React.StrictMode> {/* <-- this guy! */}
    <App />
  </React.StrictMode>
);
```

## Dependencies

The second parameter is DependencyList, which is array to define what the **useEffect** call will overwatch.

```js
useEffect(
  () => {
    const subscription = props.source.subscribe();
    return () => {
      subscription.unsubscribe();
    };
  },
  [props.source],
);
```

This *useEffect* will wait `props.source` to be changed. And then it only calls the first parameter function when the props.source changes.

> @param deps - If present, effect will only activate if the values in the list change.

## Cleanup Function

> @param effect - Imperative function that can return a cleaup function.

As you can see from the above code snippet, Effect function returns a function which is called **Cleanup**.

Then we should talk about when **Effect Function** will be called, and when is to clean up with **Cleanup Function**.

1. Effect Function will run *when the render is committed to the screen (after every completed render)*. In other words, It fires *after layout and paint*, during a deferred event.

2. Cleanup Function will *run before the component is removed* from the UI. It prevents memory leak of components. If the component renders multiple times due to various states, the *previous effect is cleaned up* first before executing the next effect.