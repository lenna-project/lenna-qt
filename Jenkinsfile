node {
  stage 'Checkout'
   checkout scm

  stage 'Build'
   sh 'mkdir -p build'
   sh 'cd build && cmake .. && make'
}
