import {createVector} from './chessboard_utils.js';

let vector = [];
for (let i = 0; i < 10; i++){
  vector[i] = Math.floor(Math.random() * 2);
}

let table = createVector(vector, '#simple-bit-mutation');
$('div', table).click(function(){ mutateBit(this);});
updateStyle();

function mutateBit(field){
  if (parseInt(field.innerHTML) === 0){
    field.innerHTML = 1;
  } else {
    field.innerHTML = 0;
  }
  updateStyle();
}

function updateStyle(){
  $('div', table).each(function(){
    if (parseInt(this.innerHTML) === 1){
      this.style.backgroundColor = '#000000';
      this.style.color = '#ffffff';

    } else {
      this.style.backgroundColor = null;
      this.style.color = null;
    }
  });
}






