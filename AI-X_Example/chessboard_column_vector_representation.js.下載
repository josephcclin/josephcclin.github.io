import {position_to_column_vector, field_to_index, index_to_field, example_positions, createVector} from './chessboard_utils.js';
import {col_name_to_index, highlightCollisions, index_to_col_name, position_to_row_vector} from './chessboard_utils.js';

let boards = initializeBoards([
  ['board-vector-example-1', '#board-vector-1'],
  ['board-vector-example-2', '#board-vector-2'],
  ['board-vector-example-3', '#board-vector-3']
]);

function initializeBoards(boardContainers){
  let boards = [];
  for (let i in boardContainers) {
    let boardContainer = boardContainers[i][0];
    let vectorContainer = boardContainers[i][1];
    //console.log(boardContainer);
    let board = Chessboard(boardContainer, {
      draggable: true,
      position: example_positions[i],
      showNotation: false,
      onDrop: onDrop,
      boardIndex: i,
      boardContainer: boardContainer,
      tableContainer: vectorContainer
    });
    boards[i] = board;

    let table = createVector(position_to_column_vector(board.position()), vectorContainer);
    $('div', table).click(function(){ mutateQueen(this, board);});
  }
  return boards;
}

function onDrop(source, target, piece, newPos, oldPos, orientation){
  if (target in oldPos || target === 'offboard' || target[0] !== source[0]){
    return 'snapback';
  }

  const divIndex = col_name_to_index[target[0]];
  const targetRow = target[1];
  const position = newPos;
  let board = boards[this.boardIndex];

  delete position[source];
  position[target] = 'bQ';
  $('div', this.tableContainer)[divIndex].innerHTML = targetRow;

  board.position(position);
}

function mutateQueen(field, board){
  let column = index_to_col_name[field.getAttribute('childindex')];
  let row = parseInt(field.innerHTML);
  let field_before = column + row;

  let new_row = Math.floor(Math.random()*8)+1;
  while (new_row === row){
    new_row = Math.floor(Math.random()*8)+1;
  }
  let field_after = column + new_row;

  let position = board.position();

  delete position[field_before]; // update board
  position[field_after] = 'bQ';
  field.innerHTML = new_row; // update matrix
  board.position(position);
}



