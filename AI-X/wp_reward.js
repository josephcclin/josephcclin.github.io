import * from "https://d3js.org/d3.v4.js" 

const line = d3.select("#Viz_area")
const svg1 = d3.select("#s01")
const svg2 = d3.select("#s02")
const svg3 = d3.select("#s03")
const svg4 = d3.select("#s04")
const svg5 = d3.select("#s05")
svg1.style("left", `${500 * (-0.8 + 1) - 57.59 / 2}px`).style("bottom", '20%')
svg2.style("left", `${500 * (1 + 1) - 57.59 / 2}px`).style("bottom", '20%')
svg3.style("left", `${500 * (0.1 + 1) - 57.59 / 2}px`).style("bottom", '20%')
svg4.style("left", `${500 * (-0.1 + 1) - 57.59 / 2}px`).style("bottom", '20%')
svg5.style("left", `${500 * (0.2 + 1) - 57.59 / 2}px`).style("bottom", '20%')
d3.select(`#t01`)
  .style("left", `${500 * (-0.8 + 1) - tipWidth / 2}px`)
  .attr("transform", `translate(${500 * (-0.8 + 1)}, 0)`)
d3.select(`#t02`)
  .style("left", `${500 * (1.1 + 1) - tipWidth / 2}px`)
  .attr("transform", `translate(${500 * (1 + 1)}, 0)`)
d3.select(`#t03`)
  .style("left", `${500 * (0.3 + 1) - tipWidth / 2}px`)
  .attr("transform", `translate(${500 * (0.1 + 1)}, 0)`)
d3.select(`#t04`)
  .style("left", `${500 * (-0.1 + 1) - tipWidth / 2}px`)
  .attr("transform", `translate(${500 * (-0.1 + 1)}, 0)`)

const wp1 = d3.select("#wp1")
const wp2 = d3.select("#wp2")
const wp3 = d3.select("#wp3")
const wp4 = d3.select("#wp4")
const wp5 = d3.select("#wp5")
const r1 = d3.select("#r1")
const r2 = d3.select("#r2")
const r3 = d3.select("#r3")
const r4 = d3.select("#r4")
const r5 = d3.select("#r5")

const setPosition = (arr, target) => {
const mid = findClosest(positions, target)
wp1.node().innerHTML = `win. prob. ${data[1][mid]}`
wp2.node().innerHTML = `win. prob. ${data[2][mid]}`
wp3.node().innerHTML = `win. prob. ${data[3][mid]}`
wp4.node().innerHTML = `win. prob. ${data[4][mid]}`
wp5.node().innerHTML = `win. prob. ${data[5][mid]}`
r1.node().innerHTML = `reward ${rs[1][mid]}`
r2.node().innerHTML = `reward ${rs[2][mid]}`
r3.node().innerHTML = `reward ${rs[3][mid]}`
r4.node().innerHTML = `reward ${rs[4][mid]}`
r5.node().innerHTML = `reward ${rs[5][mid]}`

let tp = [0, 0, 0, 0, 0]
if (positions[mid] < -0.8) tp = [-0.48, 0.9, 0.3, -0.1, -0.8]
else if (positions[mid] < -0.1) tp = [-0.8, 0.9, 0.34, -0.08, -0.48]
else if (positions[mid] < 0.1) tp = [-0.8, 0.9, 0.4, -0.4, 0]
else tp = [-0.8, 0.9, 0.13, -0.3, 0.55]

const range = [1, 2, 3, 4, 5]
range.forEach((i) => {
  d3.select(`#t0${i}`)
	.style("left", `${500 * (tp[i - 1] + 1) - tipWidth / 2}px`)
	.attr("transform", `translate(${500 * (tp[i - 1] + 1)}, 0)`)
})
svg5.transition()
	.duration(1000)
	.style("left", `${500 * (positions[mid] + 1) - 57.59 / 2}px`)
	.style("bottom", `20%`)
d3.select('#v5').remove()
line.append("circle")
  .attr("id", "v5")
  .attr("r", 10).attr("style", `left:${500 * (positions[mid] + 1) - 57.59 / 2}px;`)
  .attr("transform", `translate(${500 * (positions[mid] + 1)}, 0)`)
  .attr("fill", "#bababa")
d3.select('#l05').remove()
line.append("text")
  .attr("id", "l05")
  .attr("class", "tick-label")
  .attr("style", `left:${500 * (positions[mid] + 1) - 57.59 / 2}px;`)
  .attr("transform", `translate(${500 * (positions[mid] + 1)}, 0)`)
  .attr("y", 30)
  .attr("dy", ".35em")
  .text(positions[mid])
  .attr("fill", "#bababa")
return mid
}

const drag = d3.drag()
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
  const pivot = setPosition(positions, (d3.event.x-25) / 500 - 1)
  
  d3.select(this)
	.select('img')
	.attr("src", `./img/aix_doll-05.svg`)
})
svg5.call(drag)
const reset = () => setPosition(positions, 0.2)
d3.select('#reset').on("click", reset)

reset()
const x = d3.scaleLinear()
  .domain([-1, 1])
  .range([0, 1000])
const axis = line.call(d3.axisBottom(x))
const ticks = axis.selectAll(".tick").style("font-size",".85rem")
console.log(ticks)
ticks.each(function() { d3.select(this).append("circle").attr("r", 5).attr("fill", "black"); })
ticks.selectAll("line").remove()
const ps = [-0.8, 1, 0.1, -0.1]
const pcolor = ["#d04a5b", "#00798c", "#edae49", "#30638e"]
ps.forEach((p, i) => {
line.append("circle")
  .attr("id", `v${i + 1}`)
  .attr("r", 10).attr("style", `left:${500 * (p + 1) - 57.59 / 2}px;position: relative;`)
  .attr("transform", `translate(${500 * (p + 1)}, 0)`)
  .attr("fill", pcolor[i])
line.append("text")
  .attr("id", `l0${i + 1}`)
  .attr("class", "tick-label")
  .attr("style", `left:${500 * (p + 1) - 57.59 / 2}px;`)
  .attr("transform", `translate(${500 * (p + 1)}, 0)`)
  .attr("y", 30)
  .attr("dy", ".35em")
  .text(p)
  .attr("fill", pcolor[i])
})
justifyTips()