---
title: "React Note - 7. React Route"
last_modified_at: 2022-12-07T21:30:00-08:00
categories:
    - React
tags:
    - [react, frontend]
excerpt: "Paging has never been easier than this"
toc: true
---

We have every tools for a single page now.

It's time for a multi page system.

We are going to have a following file structures that categorizing

- **components** : main *content* items that fill out a page.
- **routes** : pages that contents are being placed.

![source structure](/_posts/react/react-note-06-route/images/source_structure.png)

> For example
>
> raacker.github.io will have the *Main.js* under routes folder.
>
> raacker.github.io/about will have the *About.js* under routes folder.
>
> *Post.js*, *CodeSnippet.js*, or any small widgets will be parts of components folder

Let's define Movie component first. Data will be a json result of *https://yts.mx/api/v2/list_movies.json?minimum_rating=8.8&sort_by=year*

```js
import PropTypes from "prop-types";

function Movie({ id, coverImage, title, year, summary, genres }) {
    return (
        <div key={ id }>
            <img src={ coverImage }></img>
            <h2>
                { title } ( { year } )
            </h2>
            <p>{ summary }</p>
            <ul>
                {
                    genres.map((genre) => {
                        return (<li>{ genre }</li>);
                    })
                }
            </ul>
        </div>
    );
}

Movie.propTypes = {
    id: PropTypes.number.isRequired,
    coverImage: PropTypes.string.isRequired,
    title: PropTypes.string.isRequired,
    year: PropTypes.string.isRequired,
    summary: PropTypes.number.isRequired,
    genres: PropTypes.array.isRequired,
}
export default Movie;
```

It covers

- Define propTypes to secure expected parameters and their types
- Return a *React Component* which shows some movie information briefly

Then we will have a Home page that list up all the movies of the query result.

```js
import { useState, useEffect } from 'react';
import Movie from '../components/Movie';

function Home() {
    const [isLoading, setLoading] = useState(true);
    const [page, setPage] = useState(0);
    const [fetchResult, setFetchResult] = useState([]);
    const getMovies = async() => {
        const response = await fetch(`https://yts.mx/api/v2/list_movies.json?minimum_rating=8.8&sort_by=year&page=${page}`);

        const json = await response.json();

        setFetchResult(json.data.movies);
        setLoading(false);
    }

    const prevPage = () => {
        setPage(curr => {
            if (curr <= 0) return 0;
            return curr - 1;
        });
    }
    const nextPage = () => {
        setPage(curr => curr + 1);
    }

    useEffect(() => {
        getMovies();
    }, [isLoading, page]);

    return (

    <div>
        <h2>Movie App</h2>
        {
            isLoading ? <b>Loading...</b> : <button onClick={ getMovies }>Refresh</button>
        }
        {
            fetchResult.length !== 0 ? <button onClick={ prevPage }>Prev Page</button> : null
        }
        {
            fetchResult.length !== 0 ? <button onClick={ nextPage }>Next Page</button> : null
        }

        {
            fetchResult.map((movie) => 
                <Movie
                    id={ movie.id }
                    coverImage={ movie.medium_cover_image }
                    title={ movie.title }
                    year={ movie.year }
                    summary={ movie.summary }
                    genres={ movie.genres }
                />
            )
        }
    </div>
    );
}

export default Home;
```

This is literally a barebone page without any styles.

It has

- Use an asynchronous function to fetch API result and apply it to the React Component.
- Use *useEffect* to update only when desired states get changed
- To render Movie data, we are using *Movie Component*.

Let's modify **App.js** to open Home.js

```js
import {
    BrowserRouter as Router,
    Routes,
    Route
} from 'react-router-dom';

import Home from './routes/Home';

function App() {
  return (
      <Router>
        <Routes>
          <Route path="/" element={ <Home /> } />
        </Routes>
      </Router>
  );
}

export default App;
```

![Home.js](/_posts/react/react-note-06-route/images/barebone_image.png)

Now, let's add a detail page we can reroute when we click a title or a poster image.

```js
import { useParams } from 'react-router-dom';
import { useState, useEffect } from 'react';

function Detail() {
    const { id } = useParams();
    const [ fetchResult, setFetchResult ] = useState([]);

    const getMovieDetail = async() => {
        const response = await fetch(`https://yts.mx/api/v2/movie_details.json?movie_id=${id}`);

        const json = await response.json();

        setFetchResult(json.data.movie);
    }

    useEffect(() => {
        getMovieDetail();
    }, []);

    return (
        <div>
            <h2>{ fetchResult.title }</h2>
            <img src={ fetchResult.background_image }></img>
            <t>{ fetchResult.description_full }</t>
        </div>
    );
}

export default Detail;
```

- See the **id** in *String literal url* and **useParams** of react-router-dom. It lets you bind parameters that you pass to the *Detail* component.

If you add a one more line to the App.js, and a **Link Component** to the Movie, it's done.

```js
function App() {
  return (
      <Router>
        <Routes>
          <Route path="/" element={ <Home /> } />
          <Route path="/movie/:id" element={ <Detail /> } />
        </Routes>
      </Router>
  );
}
```

```js
function Movie({ id, coverImage, title, year, summary, genres }) {
    return (
        <div key={ id }>
            <Link to={`/movie/${id}`}>
                <img src={ coverImage }></img>
                <h2>
                    { title } ( { year } )
                </h2>
            </Link>
            <p>{ summary }</p>
            <ul>
                {
                    genres.map((genre) => {
                        return (<li>{ genre }</li>);
                    })
                }
            </ul>
        </div>
    );
}
```

- Using colons like **`:id`** is how you determine URL with parameters.
- By using **`<Link>`**, you are rerouting URL to this component with a specific URL format which is `*/movie/${ id }*`

![Detail.js](/_posts/react/react-note-06-route/images/after_reroute.png)