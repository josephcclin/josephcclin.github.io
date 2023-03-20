import {createVector} from "./chessboard_utils.js";

let vectorNumbers = [];
let vectorCharacters = [];
for (let i = 0; i < 10; i++){
    vectorNumbers[i] = getRandomNumber();
    vectorCharacters[i] = getRandomCharacter();
}

let tableNumbers = createVector(vectorNumbers, "#simple-value-mutation-numbers");
$("div", tableNumbers).click(function(){ mutateNumber(this);});

let tableCharacters = createVector(vectorCharacters, "#simple-value-mutation-characters");
$("div", tableCharacters).click(function(){ mutateCharacter(this);});


function mutateNumber(field){
    let currentValue = parseInt(field.innerHTML);
    let newValue = getRandomNumber();
    while (newValue === currentValue){
        newValue = getRandomNumber();
    }
    field.innerHTML = newValue;
}

function mutateCharacter(field){
    let currentValue = field.innerHTML;
    let newValue = getRandomCharacter();
    while (newValue === currentValue){
        newValue = getRandomCharacter();
    }
    field.innerHTML = newValue;
}

function getRandomNumber(){
    return Math.floor(Math.random() * 10);
}

function getRandomCharacter(){
    let characters = 'abcdefghijklmnopqrstuvwxyz';
    return characters.charAt(Math.floor(Math.random() * characters.length));
}

