const apiKey = 'ef076b99225793040b2243b3b0b5b8c5';
const searchInput = document.getElementById('searchInput');
const resultsContainer = document.getElementById('results');

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

        // Přidání události na kliknutí na název filmu
        movieTitle.addEventListener('click', function() {
            showMovieDetails(movie.id);
        });

        listItem.appendChild(movieTitle);
        movieList.appendChild(listItem);
    });

    resultsContainer.appendChild(movieList);
}

async function showMovieDetails(movieId) {
    try {
        const response = await fetch(`https://api.themoviedb.org/3/movie/${movieId}?api_key=${apiKey}`);
        const movieDetails = await response.json();

        // Vytvoření modálního okna pro zobrazení detailů
        const modal = document.createElement('div');
        modal.classList.add('modal');
        modal.innerHTML = `
            <h2>${movieDetails.title}</h2>
            <p>${movieDetails.overview}</p>
            <button onclick="closeModal()">Zavřít</button>
        `;
        document.body.appendChild(modal);
    } catch (error) {
        console.error('Chyba při získávání detailů filmu:', error);
    }
}

function closeModal() {
    const modal = document.querySelector('.modal');
    document.body.removeChild(modal);
}
