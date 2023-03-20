import {squareClass, position_to_binary_board, field_to_index, index_to_field, example_positions,
  highlightCollisions} from './chessboard_utils.js';

// setup board
let board = Chessboard('board-8-queens-matrix', {
  draggable: true,
  position: example_positions[0],
  onDrop: onDrop,
  onSnapbackEnd: onSnapback
});
let $board = $('#board-8-queens-matrix');

// create matrix representation
let matrix = createMatrix(position_to_binary_board(board.position())[0], '#board-8-queens-matrix-representation');
let matrixdivs = $(matrix).find('div');
//highlightCollisions($board, board.position());

updateStyle();
function updateStyle(){
  $('div', matrix).each(function(){
    if (parseInt(this.innerHTML) === 1){
      this.style.backgroundColor = '#000000';
      this.style.color = '#ffffff';

    } else {
      this.style.backgroundColor = null;
      this.style.color = null;
    }
  });
}


/**
 *
 * @param board
 * @param chessfield
 * @param linkedmatrix
 */
function onDrop(source, target, piece, newPos, oldPos, orientation){
  if (target in oldPos || target === 'offboard'){
    return 'snapback';
  }

  const fieldTarget = field_to_index(target);
  const fieldSource = field_to_index(source);
  const position = board.position();

  delete position[source];
  position[target] = 'bQ';
  matrixdivs[fieldSource].innerHTML = 0; // update matrix
  matrixdivs[fieldTarget].innerHTML = 1; // update matrix

  board.position(position);
  //highlightCollisions($board, board.position())
  updateStyle();

}

function onSnapback(a, b, newPos, d){
  //highlightCollisions($board, newPos);
}

/**
 *
 * @param tableData
 * @param tableContainer
 * @returns {HTMLTableElement}
 */
function createMatrix(tableData, tableContainer) {
  var matrix = document.createElement('table');
  var tableBody = document.createElement('tbody');

  let i = 0;
  tableData.forEach(function(rowData) {
    rowData.forEach(function(cellData) {
      var cell = document.createElement('div');
      cell.appendChild(document.createTextNode(cellData));
      cell.setAttribute('childIndex', i);
      tableBody.appendChild(cell);
      i = i+1;
    });

    //tableBody.appendChild(row);
  });

  matrix.appendChild(tableBody);
  $(tableContainer)[0].appendChild(matrix);
  return matrix;
}

