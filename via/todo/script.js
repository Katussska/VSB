const todo = {
    id: Date.now(),
    name: "Buy milk",
    completed: false
};

// select everything
// select the todo-form
const todoForm = document.querySelector('.todo-form');
// select the input box
const todoInput = document.querySelector('.todo-input');
// select the <ul> with class="todo-items"
const todoItemsList = document.querySelector('.todo-items');

// array which stores every todos
let todos = [];

// add an eventListener on form, and listen for submit event
todoForm.addEventListener('submit', function (event) {
    // prevent the page from reloading when submitting the form
    event.preventDefault();
    addTodo(todoInput.value); // call addTodo function with input box current value
});

// function to add todo
function addTodo(item) {
    // if item is not empty
    if (item !== '') {
        // make a todo object, which has id, name, and completed properties
        const todo = {
            id: Date.now(),
            name: item,
            completed: false
        };// then add it to todos array
        todos.push(todo);
        renderTodos(todos); // then renders them between <ul>// finally clear the input box value
        todoInput.value = '';
    }
}

// function to render given todos to screen
function renderTodos(todos) {
    // clear everything inside <ul> with class=todo-items
    todoItemsList.innerHTML = '';// run through each item inside todos
    todos.forEach(function (item) {
        // check if the item is completed
        const checked = item.completed ? 'checked' : null;// make a <li> element and fill it
        // <li> </li>
        const li = document.createElement('li');
        // <li class="item"> </li>
        li.setAttribute('class', 'item');
        // <li class="item" data-key="20200708"> </li>
        li.setAttribute('data-key', item.id);
        /* <li class="item" data-key="20200708">
              <input type="checkbox" class="checkbox">
              Go to Gym
              <button class="delete-button">X</button>
            </li> */
        // if item is completed, then add a class to <li> called 'checked', which will add line-through style
        if (item.completed === true) {
            li.classList.add('checked');
        }
        li.innerHTML = `
      <input type="checkbox" class="checkbox" ${checked}>
      ${item.name}
      <button class="delete-button">X</button>
    `;
        // finally add the <li> to the <ul>
        todoItemsList.append(li);
    });
}
