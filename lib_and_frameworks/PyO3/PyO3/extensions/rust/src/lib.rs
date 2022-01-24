

use pyo3::prelude::*;

#[pyfunction]
fn double(x: usize) -> usize {
    x * 2
}


#[pyfunction]
fn sum(a: i32, b: i32) -> i32 {
    a + b
}


#[pyclass]
struct User {
    id: i64
}


#[pymethods]
impl User {
    #[new]
    fn new(id: i64) -> PyResult<Self> {
        Ok(User { id })
    }
}


/// This module is implemented in Rust.
#[pymodule]
#[pyo3(name = "extension_rust")]
fn my_extension(py: Python, m: &PyModule) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(double, m)?)?;
    m.add_function(wrap_pyfunction!(sum, m)?)?;
    Ok(())
}

