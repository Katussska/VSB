const apiKey = 'ef076b99225793040b2243b3b0b5b8c5';
const searchInput = document.getElementById('searchInput');
const resultsContainer = document.getElementById('results');
const ratingCanvas = document.getElementById('ratingChart');

searchInput.addEventListener('input', function() {
    const query = this.value;

    if (query.length > 0) {
        searchMovies(query);
    } else {
        resultsContainer.innerHTML = '';
    }
});

async function searchMovies(query) {
    try {
        const response = await fetch(`https://api.themoviedb.org/3/search/movie?api_key=${apiKey}&query=${query}`);
        const data = await response.json();

        displayResults(data.results);
    } catch (error) {
        console.error('Chyba při získávání dat:', error);
    }
}

function displayResults(movies) {
    resultsContainer.innerHTML = '';

    if (movies.length === 0) {
        resultsContainer.innerHTML = 'Žádné výsledky.';
        return;
    }

    const movieList = document.createElement('ul');

    movies.forEach(movie => {
        const listItem = document.createElement('li');
        const movieTitle = document.createElement('span');

        movieTitle.textContent = movie.title;
        movieTitle.classList.add('movieItem');

        movieTitle.addEventListener('click', async function() {
            const description = await getMovieDescription(movie.id);
            const rating = await getMovieRating(movie.id);

            showMovieDetails(movie.title, description, rating);
        });

        listItem.appendChild(movieTitle);
        movieList.appendChild(listItem);
    });

    resultsContainer.appendChild(movieList);
}

async function getMovieDescription(movieId) {
    try {
        const response = await fetch(`https://api.themoviedb.org/3/movie/${movieId}?api_key=${apiKey}`);
        const movieDetails = await response.json();
        return movieDetails.overview;
    } catch (error) {
        console.error('Chyba při získávání popisu filmu:', error);
        return null;
    }
}

async function getMovieRating(movieId) {
    try {
        const response = await fetch(`https://api.themoviedb.org/3/movie/${movieId}?api_key=${apiKey}`);
        const movieDetails = await response.json();
        return movieDetails.vote_average;
    } catch (error) {
        console.error('Chyba při získávání hodnocení filmu:', error);
        return null;
    }
}

function showMovieDetails(title, description, rating) {
    resultsContainer.innerHTML = `
        <h2>${title}</h2>
        <p><strong>Popis:</strong> ${description}</p>
    `;

    if (rating !== null) {
        const ctx = ratingCanvas.getContext('2d');
        new Chart(ctx, {
            type: 'bar',
            data: {
                labels: ['Hodnocení'],
                datasets: [{
                    label: 'Hodnocení filmu',
                    data: [rating],
                    backgroundColor: 'rgba(54, 162, 235, 0.2)',
                    borderColor: 'rgba(54, 162, 235, 1)',
                    borderWidth: 1
                }]
            },
            options: {
                scales: {
                    y: {
                        beginAtZero: true
                    }
                }
            }
        });
    } else {
        console.log('Nelze načíst hodnocení filmu.');
    }
}


