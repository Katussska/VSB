function fetchMovieDescription(event) {
    event.preventDefault();

    const movieName = document.getElementById('movieName').value.trim();
    if (movieName === '') {
        alert('Zadej název filmu!');
        return;
    }

    const apiKey = 'ef076b99225793040b2243b3b0b5b8c5'; // Nahraď skutečným API klíčem z TMDB

    fetch(`https://api.themoviedb.org/3/search/movie?api_key=${apiKey}&query=${movieName}`)
        .then(response => response.json())
        .then(data => {
            const movie = data.results[0];
            if (movie) {
                const movieDescription = movie.overview || 'Popis není k dispozici.';
                const resultDiv = document.getElementById('result');
                resultDiv.innerHTML = `<h2>${movie.title}</h2><p>${movieDescription}</p>`;
                resultDiv.style.display = 'block'; // Zobrazí div se výsledkem
            } else {
                alert('Film nebyl nalezen.');
            }
        })
        .catch(error => {
            console.error('Chyba při získávání dat:', error);
            alert('Došlo k chybě, zkuste to prosím znovu.');
        });
}

document.querySelector('button').addEventListener('click', fetchMovieDescription);
