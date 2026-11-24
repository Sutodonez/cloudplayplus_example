#!/usr/bin/env node
/** Spawn rea.mjs and write UTF-8 stdout/stderr files. Usage: node _run-rea-utf8.js <outfile> -- <rea args...> */
const { spawn } = require("child_process");
const fs = require("fs");
const out = process.argv[2];
const sep = process.argv.indexOf("--");
if (!out || sep < 0) {
  console.error("usage: node _run-rea-utf8.js <outfile> -- <rea args...>");
  process.exit(2);
}
const args = process.argv.slice(sep + 1);
const child = spawn(
  process.execPath,
  ["D:/Documents/Projects/.REA/scripts/rea.mjs", ...args],
  { env: process.env, stdio: ["ignore", "pipe", "pipe"] },
);
let stdout = Buffer.alloc(0);
let stderr = Buffer.alloc(0);
const t0 = Date.now();
process.stdout.write(`RUN ${args.join(" ")}\n`);
child.stdout.on("data", (d) => {
  stdout = Buffer.concat([stdout, d]);
});
child.stderr.on("data", (d) => {
  stderr = Buffer.concat([stderr, d]);
});
child.on("close", (code) => {
  fs.writeFileSync(out, stdout);
  fs.writeFileSync(out + ".err", stderr);
  const t = stdout.toString("utf8").replace(/^\uFEFF/, "").trim();
  process.stdout.write(`DONE exit=${code} ms=${Date.now() - t0} bytes=${stdout.length}\n`);
  try {
    const j = JSON.parse(t);
    if (j.error || (j.code && j.message && !j.normalized_result && !j.raw_result && j.category)) {
      console.log("ERR", j.code, (j.message || "").slice(0, 240));
      if (j.remediation) console.log("remediation", JSON.stringify(j.remediation));
    } else {
      const r = j.normalized_result ?? j.raw_result;
      console.log("OK", JSON.stringify(r).slice(0, 900));
    }
  } catch (e) {
    console.log("parsefail", e.message, t.slice(0, 200));
  }
  process.exit(code || 0);
});
