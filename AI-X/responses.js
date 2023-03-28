const line2 = d3.select("#Viz_area2")
const svg6 = d3.select("#s06")
const svg7 = d3.select("#s07")
const svg8 = d3.select("#s08")
const svg9 = d3.select("#s09")
const svg10 = d3.select("#s010")
svg6.transition().attr("style", `left:${500 * (-0.8 + 1) - 57.59 / 2}px;bottom: 20%;`)
svg7.transition().attr("style", `left:${500 * (1 + 1) - 57.59 / 2}px;bottom: 20%;`)
svg8.transition().attr("style", `left:${500 * (0.1 + 1) - 57.59 / 2}px;bottom: 20%;`)
svg9.transition().attr("style", `left:${500 * (-0.1 + 1) - 57.59 / 2}px;bottom: 20%;`)
svg10.transition().attr("style", `left:${500 * (0.2 + 1) - 57.59 / 2}px;bottom: 20%;cursor: grab;`)

const wp6 = d3.select("#wp6")
const wp7 = d3.select("#wp7")
const wp8 = d3.select("#wp8")
const wp9 = d3.select("#wp9")
const wp10 = d3.select("#wp10")
const r6 = d3.select("#r6")
const r7 = d3.select("#r7")
const r8 = d3.select("#r8")
const r9 = d3.select("#r9")
const r10 = d3.select("#r10")


const setPointAndLabel = (ps, pcolor) => {
  ps.forEach((p, i) => {
	d3.select(`v${i + 6}`).remove()
	d3.select(`l0${i + 6}`).remove()
	line2.append("circle")
	  .attr("id", `v${i + 6}`)
	  .attr("r", 10).attr("style", `left:${500 * (p + 1) - 57.59 / 2}px;position: relative;`)
	  .attr("transform", `translate(${500 * (p + 1)}, 0)`)
	  .attr("fill", pcolor[i])
	line2.append("text")
	  .attr("id", `l0${i + 6}`)
	  .attr("class", "tick-label")
	  .attr("style", `left:${500 * (p + 1) - 57.59 / 2}px;`)
	  .attr("transform", `translate(${500 * (p + 1)}, 0)`)
	  .attr("y", 30)
	  .attr("dy", ".35em")
	  .text(p)
	  .attr("fill", pcolor[i])
  })
}

const setPosition2 = (arr, target) => {
  d3.selectAll('.extratip').remove()
  d3.selectAll('.extraPoint').remove()
  d3.selectAll('.extraLabel').remove()
  d3.selectAll(`.tip`).style('display', 'flex')
  d3.select('#l010').remove()

  const mid = findClosest(positions, target)
  svg6.transition().attr("style", `left:${500 * (-0.8 + 1) - 57.59 / 2}px;bottom: 20%;`)
  svg7.transition().attr("style", `left:${500 * (1 + 1) - 57.59 / 2}px;bottom: 20%;`)
  svg8.transition().attr("style", `left:${500 * (0.1 + 1) - 57.59 / 2}px;bottom: 20%;`)
  svg9.transition().attr("style", `left:${500 * (-0.1 + 1) - 57.59 / 2}px;bottom: 20%;`)
  svg8
	  .select('img')
	  .attr("src", `./img/aix_doll-03.svg`)
  svg9
	.select('img')
	.attr("src", `./img/aix_doll-04.svg`)
  d3.select('#i01').attr("style", `display: ${Math.abs(-0.8 - target) < 0.2 ? 'flex' : 'none'};`)
  d3.select('#i02').attr("style", `display: ${Math.abs(1 - target) < 0.2 ? 'flex' : 'none'};`)
  d3.select('#i03').attr("style", `display: ${Math.abs(0.1 - target) < 0.2 ? 'flex' : 'none'};`)
  d3.select('#i04').attr("style", `display: ${Math.abs(-0.1 - target) < 0.2 ? 'flex' : 'none'};`)
  wp6.node().innerHTML = `win. prob. ${data[1][mid]}`
  wp7.node().innerHTML = `win. prob. ${data[2][mid]}`
  wp8.node().innerHTML = `win. prob. ${data[3][mid]}`
  wp9.node().innerHTML = `win. prob. ${data[4][mid]}`
  wp10.node().innerHTML = `win. prob. ${data[5][mid]}`
  r6.node().innerHTML = `reward ${rs[1][mid]}`
  r7.node().innerHTML = `reward ${rs[2][mid]}`
  r8.node().innerHTML = `reward ${rs[3][mid]}`
  r9.node().innerHTML = `reward ${rs[4][mid]}`
  r10.node().innerHTML = `reward ${rs[5][mid]}`

  let tp = [0, 0, 0, 0, 0]
  if (positions[mid] < -0.8) tp = [-0.48, 0.9, 0.3, -0.1, -0.8]
  else if (positions[mid] < -0.1) tp = [-0.8, 0.9, 0.34, -0.08, -0.48]
  else if (positions[mid] < 0.1) tp = [-0.8, 0.9, 0.4, -0.4, 0]
  else tp = [-0.8, 0.9, 0.13, -0.3, 0.55]

  const range = [6, 7, 8, 9, 10]
  range.forEach((i) => {
	console.log(i)
	d3.select(`#t0${i}`)
	  .style("left", `${500 * (tp[i - 6] + 1) - tipWidth / 2}px`)
	  .attr("transform", `translate(${500 * (tp[i - 6] + 1)}, 0)`)
  })
  svg10.transition()
	  .duration(1000)
	  .attr("style", 
		`left:${500 * (positions[mid] + 1) - 57.59 / 2}px;bottom: 20%;;cursor: grab;`
	  )
  svg10
	.select('img')
	.attr("src", `./img/aix_doll-05.svg`)
  d3.select('#v10').remove()
  line2.append("circle")
	.attr("id", "v10")
	.attr("r", 10).attr("style", `left:${500 * (positions[mid] + 1) - 57.59 / 2}px;`)
	.attr("transform", `translate(${500 * (positions[mid] + 1)}, 0)`)
	.attr("fill", "#bababa")
  setPointAndLabel([-0.8, 1, 0.1, -0.1], ["#d04a5b", "#00798c", "#edae49", "#30638e"])
  line2.append("text")
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

const setGroups = (number) => {
  d3.selectAll('.extratip').remove()
  d3.selectAll(`.tip`).style('display', 'flex')
  const target = combinations[number]
  const { group, position, tp, wp, r } = target
  d3.select('#i01').attr("style", `display: none;`)
  d3.select('#i02').attr("style", `display: none;`)
  d3.select('#i03').attr("style", `display: none;`)
  d3.select('#i04').attr("style", `display: none;`)
  d3.selectAll('.extraPoint').remove()
  d3.selectAll('.extraLabel').remove()
  group.forEach((g, i) => {
	g.forEach((e, j) => {
	  console.log(`#s0${e + 5}`)
	  d3.select(`#s0${e + 5}`)
		.transition()
		.duration(1000)
		.style("left",
		  `${500 * (position[i] + 1) - 57.59 * (g.length / 2 - j)}px`
		)
	  d3.select(`#t0${e + 5}`)
		.style("left", `${500 * (tp[i] + 1) - tipWidth / 2}px`)
		.attr("transform", `translate(${500 * (tp[i] + 1)}, 0)`)
	  d3.select(`#wp${e + 5}`).node().innerHTML = `win. prob. ${wp[i]}`
	  d3.select(`#r${e + 5}`).node().innerHTML = `reward ${r[i]}`
	})
	if (g.length > 1) {
	  const tcolor = ['#d04a5c23', '#02798c33', '#ffc1073b', '#4a6bd023', '#bababa69']
	  const extrabox = d3.select('#box2')
		.append("div")
		.attr('class', 'tip extratip')
		.style('background-color', tcolor[g[0] - 1])
		.style('left', `${500 * (tp[i] + 1) - 90}px`)
	  extrabox.append("p")
		.attr('class', "mb-0 small")
		.node()
		.innerHTML = `win. prob. ${wp[i]}`
	  g.forEach((n) => {
		d3.selectAll(`#v${n + 5}`).remove()
		d3.selectAll(`#l0${n + 5}`).remove()
		extrabox.append("p")
		  .attr('class', "mb-0 small")
		  .node()
		  .innerHTML = `reward of ${n}. ${r[n - 1]}`
		console.log(n + 5)
		d3.select(`#t0${n + 5}`).style('display', 'none')
	  })
	  const colors = {
		1: "#d04a5b",
		2: "#00798c",
		3: "#edae49",
		4: "#30638e",
	  }
	  line2.append("circle")
		.attr("class", "extraPoint")
		.attr("r", 10).attr("style", `left:${500 * (position[i] + 1)}px;`)
		.attr("transform", `translate(${500 * (position[i] + 1)}, 0)`)
		.attr("fill", colors[g[0]])
	  line2.append("text")
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
  svg10
	.select('img')
	.attr("src", `./img/aix_doll-05-${number === 5 ? '2' : number}.svg`)
  if (number === 5) {
	svg8
	  .select('img')
	  .attr("src", `./img/aix_doll-03-best.svg`)
	svg9
	  .select('img')
	  .attr("src", `./img/aix_doll-04-best.svg`)
  } else {
	svg8
	  .select('img')
	  .attr("src", `./img/aix_doll-03.svg`)
	svg9
	  .select('img')
	  .attr("src", `./img/aix_doll-04.svg`)
  }
  justifyTips()
}

const drag2 = d3.drag()
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
	const target = (d3.event.x-25 - 500) / 500
	const pivot = setPosition2(positions, (d3.event.x-25) / 500 - 1)
	d3.select(this)
	  .select('img')
	  .attr("src", `./img/aix_doll-05.svg`)
  })
svg10.call(drag2)
const reset2 = () => setPosition2(positions, 0.2)
d3.select('#i01').on("click", () => setGroups(1))
d3.select('#i02').on("click", () => setGroups(2))
d3.select('#i03').on("click", () => setGroups(3))
d3.select('#i04').on("click", () => setGroups(4))
d3.select('#best').on("click", () => setGroups(5))
d3.select('#reset2').on("click", reset2)

reset2()
const x2 = d3.scaleLinear()
	.domain([-1, 1])
	.range([0, 1000])
const axis2 = line2.call(d3.axisBottom(x2))
const ticks2 = axis2.selectAll(".tick")
ticks2.each(function() { d3.select(this).append("circle").attr("r", 5).attr("fill", "black"); })
ticks2.selectAll("line").remove()