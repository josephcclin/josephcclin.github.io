const line3 = d3.select("#Viz_area3")
const svg11 = d3.select("#s011")
const svg12 = d3.select("#s012")
const svg13 = d3.select("#s013")
const svg14 = d3.select("#s014")
const svg15 = d3.select("#s015")
svg11.transition().attr("style", `left:${500 * (-0.8 + 1) - 57.59 / 2}px;bottom: 20%;`)
svg12.transition().attr("style", `left:${500 * (1 + 1) - 57.59 / 2}px;bottom: 20%;`)
svg13.transition().attr("style", `left:${500 * (0.1 + 1) - 57.59 / 2}px;bottom: 20%;`)
svg14.transition().attr("style", `left:${500 * (-0.1 + 1) - 57.59 / 2}px;bottom: 20%;`)
svg15.transition().attr("style", `left:${500 * (0.2 + 1) - 57.59 / 2}px;bottom: 20%;cursor: grab;`)

const wp11 = d3.select("#wp11")
const wp12 = d3.select("#wp12")
const wp13 = d3.select("#wp13")
const wp14 = d3.select("#wp14")
const wp15 = d3.select("#wp15")
const r11 = d3.select("#r11")
const r12 = d3.select("#r12")
const r13 = d3.select("#r13")
const r14 = d3.select("#r14")
const r15 = d3.select("#r15")


const setPointAndLabel2 = (ps, pcolor) => {
  ps.forEach((p, i) => {
	d3.select(`v${i + 11}`).remove()
	d3.select(`l0${i + 11}`).remove()
	line2.append("circle")
	  .attr("id", `v${i + 11}`)
	  .attr("r", 10).attr("style", `left:${500 * (p + 1) - 57.59 / 2}px;position: relative;`)
	  .attr("transform", `translate(${500 * (p + 1)}, 0)`)
	  .attr("fill", pcolor[i])
	line2.append("text")
	  .attr("id", `l0${i + 11}`)
	  .attr("class", "tick-label")
	  .attr("style", `left:${500 * (p + 1) - 57.59 / 2}px;`)
	  .attr("transform", `translate(${500 * (p + 1)}, 0)`)
	  .attr("y", 30)
	  .attr("dy", ".35em")
	  .text(p)
	  .attr("fill", pcolor[i])
  })
}

const tipcolor = ['#f8e6e8', '#d3e5e9', '#fff0d1', '#e5ebf9', '#e3e3e3']
const tipDelay = 300
svg11.on('mouseover', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 1)
	d3.select("#leftTip").style("background-color", tipcolor[0]).node().innerHTML = 'myopic reward of 1: 0.1056'
	d3.select("#rightTip").style("background-color", tipcolor[0]).node().innerHTML = 'myopic reward of 1: -0.2450'
  }, tipDelay)
})
svg11.on('mouseleave', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 0)
  }, tipDelay)
})
svg12.on('mouseover', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 1)
	d3.select("#leftTip").style("background-color", tipcolor[1]).node().innerHTML = 'myopic reward of 2: -0.1319'
	d3.select("#rightTip").style("background-color", tipcolor[1]).node().innerHTML = 'myopic reward of 2: 0.3062'
  }, tipDelay)
})
svg12.on('mouseleave', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 0)
  }, tipDelay)
})
svg13.on('mouseover', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 1)
	d3.select("#leftTip").style("background-color", tipcolor[2]).node().innerHTML = 'myopic reward of 3: 0.0132'
	d3.select("#rightTip").style("background-color", tipcolor[2]).node().innerHTML = 'myopic reward of 3: 0.0306'
  }, tipDelay)
})
svg13.on('mouseleave', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 0)
  }, tipDelay)
})
svg14.on('mouseover', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 1)
	d3.select("#leftTip").style("background-color", tipcolor[3]).node().innerHTML = 'myopic reward of 4: 0.0132'
	d3.select("#rightTip").style("background-color", tipcolor[3]).node().innerHTML = 'myopic reward of 4: -0.0306'
  }, tipDelay)
})
svg14.on('mouseleave', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 0)
  }, tipDelay)
})
svg15.on('mouseover', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 1)
	d3.select("#leftTip").style("background-color", tipcolor[4]).node().innerHTML = 'myopic reward of 5: -0.0264'
	d3.select("#rightTip").style("background-color", tipcolor[4]).node().innerHTML = 'myopic reward of 5: 0.0613'
  }, tipDelay)
})
svg15.on('mouseleave', () => {
  setTimeout(function() {
	d3.select("#myopic").transition().duration(300).style("opacity", 0)
  }, tipDelay)
})

const setPosition3 = (arr, target) => {
  d3.selectAll('.extratip').remove()
  d3.selectAll('.extraPoint').remove()
  d3.selectAll('.extraLabel').remove()
  d3.selectAll(`.tip`).style('display', 'flex')
  d3.select('#l015').remove()

  const mid = findClosest(positions, target)
  svg11.transition().attr("style", `left:${500 * (-0.8 + 1) - 57.59 / 2}px;bottom: 20%;`)
  svg12.transition().attr("style", `left:${500 * (1 + 1) - 57.59 / 2}px;bottom: 20%;`)
  svg13.transition().attr("style", `left:${500 * (0.1 + 1) - 57.59 / 2}px;bottom: 20%;`)
  svg14.transition().attr("style", `left:${500 * (-0.1 + 1) - 57.59 / 2}px;bottom: 20%;`)
  svg13
	  .select('img')
	  .attr("src", `./img/aix_doll-03.svg`)
  svg14
	.select('img')
	.attr("src", `./img/aix_doll-04.svg`)
  // d3.select('#i06').attr("style", `display: ${Math.abs(-0.8 - target) < 0.2 ? 'flex' : 'none'};`)
  // d3.select('#i07').attr("style", `display: ${Math.abs(1 - target) < 0.2 ? 'flex' : 'none'};`)
  // d3.select('#i08').attr("style", `display: ${Math.abs(0.1 - target) < 0.2 ? 'flex' : 'none'};`)
  // d3.select('#i09').attr("style", `display: ${Math.abs(-0.1 - target) < 0.2 ? 'flex' : 'none'};`)
  wp11.node().innerHTML = `win. prob. ${data[1][mid]}`
  wp12.node().innerHTML = `win. prob. ${data[2][mid]}`
  wp13.node().innerHTML = `win. prob. ${data[3][mid]}`
  wp14.node().innerHTML = `win. prob. ${data[4][mid]}`
  wp15.node().innerHTML = `win. prob. ${data[5][mid]}`
  r11.node().innerHTML = `reward ${rs[1][mid]}`
  r12.node().innerHTML = `reward ${rs[2][mid]}`
  r13.node().innerHTML = `reward ${rs[3][mid]}`
  r14.node().innerHTML = `reward ${rs[4][mid]}`
  r15.node().innerHTML = `reward ${rs[5][mid]}`

  let tp = [0, 0, 0, 0, 0]
  if (positions[mid] < -0.8) tp = [-0.48, 0.9, 0.3, -0.1, -0.8]
  else if (positions[mid] < -0.1) tp = [-0.8, 0.9, 0.34, -0.08, -0.48]
  else if (positions[mid] < 0.1) tp = [-0.8, 0.9, 0.4, -0.4, 0]
  else tp = [-0.8, 0.9, 0.13, -0.3, 0.55]

  const range = [11, 12, 13, 14, 15]
  range.forEach((i) => {
	console.log(i)
	d3.select(`#t0${i}`)
	  .style("left", `${500 * (tp[i - 11] + 1) - tipWidth / 2}px`)
	  .attr("transform", `translate(${500 * (tp[i - 11] + 1)}, 0)`)
  })
  svg15.transition()
	  .duration(1000)
	  .attr("style", 
		`left:${500 * (positions[mid] + 1) - 57.59 / 2}px;bottom: 20%;;cursor: grab;`
	  )
  svg15
	.select('img')
	.attr("src", `./img/aix_doll-05.svg`)
  d3.select('#v15').remove()
  line2.append("circle")
	.attr("id", "v15")
	.attr("r", 10).attr("style", `left:${500 * (positions[mid] + 1) - 57.59 / 2}px;`)
	.attr("transform", `translate(${500 * (positions[mid] + 1)}, 0)`)
	.attr("fill", "#bababa")
  setPointAndLabel2([-0.8, 1, 0.1, -0.1], ["#d04a5b", "#00798c", "#edae49", "#30638e"])
  line3.append("text")
	  .attr("id", "l010")
	  .attr("class", "tick-label")
	  .attr("style", `left:${500 * (positions[mid] + 1) - 57.59 / 2}px;`)
	  .attr("transform", `translate(${500 * (positions[mid] + 1)}, 0)`)
	  .attr("y", 30)
	  .attr("dy", ".35em")
	  .text(positions[mid])
	  .attr("fill", "#bababa")
  return mid
}

const setGroups2 = (number) => {
  d3.selectAll('.extratip').remove()
  d3.selectAll(`.tip`).style('display', 'flex')
  const target = combinations[number]
  const { group, position, tp, wp, r } = target
  // d3.select('#i06').attr("style", `display: none;`)
  // d3.select('#i07').attr("style", `display: none;`)
  // d3.select('#i08').attr("style", `display: none;`)
  // d3.select('#i09').attr("style", `display: none;`)
  d3.selectAll('.extraPoint').remove()
  d3.selectAll('.extraLabel').remove()
  group.forEach((g, i) => {
	g.forEach((e, j) => {
	  console.log(`#s0${e + 10}`)
	  d3.select(`#s0${e + 10}`)
		.transition()
		.duration(1000)
		.style("left",
		  `${500 * (position[i] + 1) - 57.59 * (g.length / 2 - j)}px`
		)
		.style("bottom",
		  '20%'
		)
	  d3.select(`#t0${e + 10}`)
		.style("left", `${500 * (tp[i] + 1) - tipWidth / 2}px`)
		.attr("transform", `translate(${500 * (tp[i] + 1)}, 0)`)
	  d3.select(`#wp${e + 10}`).node().innerHTML = `win. prob. ${wp[i]}`
	  d3.select(`#r${e + 10}`).node().innerHTML = `reward ${r[i]}`
	})
	if (g.length > 1) {
	  const tcolor = ['#d04a5c23', '#02798c33', '#ffc1073b', '#4a6bd023', '#bababa69']
	  const extrabox = d3.select('#box3')
		.append("div")
		.attr('class', 'tip extratip')
		.style('background-color', tcolor[g[0] - 1])
		.style('left', `${500 * (tp[i] + 1) - 90}px`)
	  extrabox.append("p")
		.attr('class', "mb-0 small")
		.node()
		.innerHTML = `win. prob. ${wp[i]}`
	  g.forEach((n) => {
		d3.selectAll(`#v${n + 10}`).remove()
		d3.selectAll(`#l0${n + 10}`).remove()
		extrabox.append("p")
		  .attr('class', "mb-0 small")
		  .node()
		  .innerHTML = `reward of ${n}. ${r[n - 1]}`
		d3.select(`#t0${n + 10}`).style('display', 'none')
	  })
	  const colors = {
		1: "#d04a5b",
		2: "#00798c",
		3: "#edae49",
		4: "#30638e",
	  }
	  line3.append("circle")
		.attr("class", "extraPoint")
		.attr("r", 10).attr("style", `left:${500 * (position[i] + 1)}px;`)
		.attr("transform", `translate(${500 * (position[i] + 1)}, 0)`)
		.attr("fill", colors[g[0]])
	  line3.append("text")
		.attr("id", `l0${i + 6}`)
		.attr("class", "extraLabel tick-label")
		.attr("style", `left:${500 * (position[i] + 1)}px;`)
		.attr("transform", `translate(${500 * (position[i] + 1)}, 0)`)
		.attr("y", 30)
		.attr("dy", ".35em")
		.text(position[i])
		.attr("fill", ["#d04a5b", "#00798c", "#edae49", "#30638e"][g[0] - 1])
	}
  })
  svg15
	.select('img')
	.attr("src", `./img/aix_doll-05-${number === 5 ? '2' : number}.svg`)
  if (number === 5) {
	svg13
	  .select('img')
	  .attr("src", `./img/aix_doll-03-best.svg`)
	svg14
	  .select('img')
	  .attr("src", `./img/aix_doll-04-best.svg`)
  } else {
	svg13
	  .select('img')
	  .attr("src", `./img/aix_doll-03.svg`)
	svg14
	  .select('img')
	  .attr("src", `./img/aix_doll-04.svg`)
  }
  justifyTips()
}

const drag3 = d3.drag()
  .on('start', function(){
	d3.select(this)
	  .select('img')
		.attr("src", `./img/aix-doll5-ani.gif`)
	})
  .on('drag', function(){
	d3.select(this)
	  .attr("style",
		`left:${d3.event.x-25}px;bottom:${-d3.event.y+100}px;cursor: grab;`
	  )
	})
  .on('end', function(){
	// const target = (d3.event.x-25 - 500) / 500
	// const pivot = setPosition3(positions, (d3.event.x-25) / 500 - 1)
	// d3.select(this)
	//   .select('img')
	//   .attr("src", `./img/aix_doll-05.svg`)
	setGroups2(5)
  })
svg15.call(drag3)
const reset3 = () => setPosition3(positions, 0.2)
// d3.select('#i01').on("click", () => setGroups(1))
// d3.select('#i02').on("click", () => setGroups(2))
// d3.select('#i03').on("click", () => setGroups(3))
// d3.select('#i04').on("click", () => setGroups(4))
// d3.select('#best').on("click", () => setGroups(5))
// d3.select('#reset2').on("click", reset2)

// reset2()
setGroups2(5)
const x3 = d3.scaleLinear()
	.domain([-1, 1])
	.range([0, 1000])
const axis3 = line3.call(d3.axisBottom(x3))
const ticks3 = axis3.selectAll(".tick")
ticks3.each(function() { d3.select(this).append("circle").attr("r", 5).attr("fill", "black"); })
ticks3.selectAll("line").remove()