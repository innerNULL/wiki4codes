/// file: index.js
/// date: 2023-12-21


const better_sqlite3 = require('better-sqlite3');


module.exports = async function(context) {
  console.log("better-sqlite3 examples starting");
  const db = better_sqlite3(':memory:', { verbose: console.log });
  
  // Create table
  const createTableSql = `
    create table if not exists example0_table (
      id bigints, 
      value string
    );
  `;
  await db.exec(createTableSql); 
  console.log("Finished creating table 'example0_table'");

  // Insert records
  const insert = db.prepare(`
    insert into example0_table (id, value) values (@id, @value);
  `);
  const records = [];
  const records_num = 100
  for (let i = 0; i < records_num; i++) {
    records.push(
      {"id": i, "value": "value" + i.toString()}
    );
  }
  const batchInsert = await db.transaction((records) => {
    for (const record of records) {
      insert.run(record);
    }
  });
  await batchInsert(records);
  console.log("Finished inserting data to table 'example0_table'");

  // Query results from table
  const stmt = db.prepare('select * from example0_table;'); 
  const results = await stmt.all();
  console.log(results);
  console.log("Finished running one query");

  console.log("better-sqlite3 examples end");
};
