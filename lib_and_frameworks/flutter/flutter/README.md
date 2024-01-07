
## Introductions
### Flutter Installation
* Install JDK1.8 (NOT JRE)
* Android SDK
* Install Flutter

## Apps Examples
### Example 0: Very Simple Flutter Demo Apps
* Project Initialization
```sh
flutter create example_0
```
* Project Run
```sh
cd example_0 && flutter run

# On Android emulator
cd example_0 && flutter run -d emulator-5554
```

### Example 1: Flutter With Native Cpp Implementation Integrated
* Project Initialization
```sh
flutter create --platforms=android,ios,macos,windows,linux --template=plugin_ffi example_1_native_cpp_integrated
```
* Project Run
```sh
# On Android emulator
cd example_1_native_cpp_integrated/example && flutter run -d emulator-5554
```
* References
  * [Using FFI in a Flutter plugin](https://codelabs.developers.google.com/codelabs/flutter-ffigen#0)  
  *[Binding to native Android code using dart:ffi](https://docs.flutter.dev/platform-integration/android/c-interop)  
