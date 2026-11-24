const fs = require("fs");
const p = fs.readFileSync(process.argv[2], "utf8");
const strs = [
  ...new Set([...p.matchAll(/"([^"]{4,120})"/g)].map((m) => m[1])),
];
const cps = [...p.matchAll(/CreateProcess\w*/g)].map((m) => m[0]);
console.log(strs.join("\n"));
console.log("CreateProcess=" + cps.join(","));
