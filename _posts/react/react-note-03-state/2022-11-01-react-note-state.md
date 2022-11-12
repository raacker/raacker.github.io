---
title: "React Note - 3. State"
last_modified_at: 2022-11-01T00:10:00-08:00
categories:
    - React
tags:
    - [react, frontend]
excerpt: "State management made React very powerful. Even with the hook system, they made it even more simpler and more powerful"
toc: true
---

# React Note - State

## State?

State & [Props](https://raacker.github.io/react/react-note-props/) are the core concept of the React framework which empower the modularity and efficiency of components.

React introduced **React Hook** in React 16.8 and it's more like the only thing you should know rather than Class component nowadays.

```js
<script type="text/bable">
    const App = () => {
        const [value, setValue] = React.useState(0);
        return (
            <div>
                { /* Wrap JS code (including comments) within a parenthesis */ } 
                <h2>{ value }</h2>
                <button onClick={ () => setValue(25) }>

                </button>
            </div>
        );
    };
    const root = document.getElementById("root");
    ReactDOM.render(<App />, root);
</script>
```

## Another Demonstration

```js
const MinuteToHourConverter = () => {
    const [minutes, setMinutes] = React.useState(0);
    const [flipped, setFlipped] = React.useState(false);
    const onChangeMinute = (e) => {
        setMinutes(e.target.value);
    };
    const onChangeHour = (e) => {
        setMinutes(e.target.value * 60);
    };
    const onReset = () => setMinutes(0);
    const onFlip = () => setFlipped(curr => !curr);
    
    return (
        <div>
            <div>
                <label htmlFor="minute_input">Minutes</label>
                <input value={minutes} id="minute_input" placeholder="Minutes" type="number" disabled={flipped === true}
                    onChange={onChangeMinute}/>
            </div>
            <div>
                <label htmlFor="hour_input">Hours</label>
                <input value={minutes / 60} id="hour_input" placeholder="Hours" type="number" disabled={flipped === false}
                    onChange={onChangeHour} />
            </div>
            <div>
                <button onClick={onReset}>
                    Reset
                </button>
                <button onClick={onFlip}>
                    Flip
                </button>
            </div>
        </div>
    );
}
```

By using a state value <code>minutes</code> we are controlling two input components at the same time.

## State may be not updating when you'd expect

Can you guarantee the *counter* of below code is being correctly updated at <code>console.log(counter)</code>?

```js
const [counter, setCounter] = React.useState(0);

function foo() {
    // You cannot guarantee the counter will be properly referenced and used at right timing
    setCounter(counter + 1);

    // What I am will be? 0? 1? 
    console.log(counter);
}
```

The function <code>foo</code> means you are calling <code>setCounter</code> with the state value.

The answer is: We can't. 

The updating state value will not be processed immediately(it will be blazing fast but still not an immediate). Because *setState* will be scheduled during [*reconcilation phase*](https://reactjs.org/docs/reconciliation.html) and you don't know when is its turn.

Check the official document.
[reactjs : State Updates May be Asynchronous](https://reactjs.org/docs/state-and-lifecycle.html#state-updates-may-be-asynchronous)

The suggested way of using <code>setCounter</code> would be

```js
const [counter, setCounter] = React.useState(0);

function foo() {
    setCounter((curr) => curr + 1);

    // result will be guaranteed
    console.log(counter);
}
```

Using arrow function ensures to take the current state internally and will update the state value accordingly.

And since the state variable is exposed externally, there is a chance that it is out of control from your scope (which you should not!)



### Readings

[Why my setState doesn't work](https://ozmoroz.com/2018/11/why-my-setstate-doesnt-work/)
