ARG CACHE_TAG=latest
ARG GRAAL_GIT_TAG=vm-1.0.0-rc9

FROM cicro/benchmark-harness:${CACHE_TAG} as harness

FROM cicro/sulong:${GRAAL_GIT_TAG}

MAINTAINER Thomas Pointhuber <thomas.pointhuber@gmx.at>

# our main dependencies
RUN apt-get update && apt-get install -y --no-install-recommends build-essential cmake file clang-6.0 llvm libomp-dev ca-certificates libpapi-dev python3 python3-psutil python3-pip python3-setuptools
RUN pip3 install wllvm

# place to store results
VOLUME /data

# our benchmarking project
COPY --from=harness /benchmarks /benchmarks

# configure benchmark enviroment
RUN echo "CLANG=/usr/bin/clang-6.0" > /benchmarks/configs/env \
    && echo "LLVM_COMPILER=clang" >> /benchmarks/configs/env \
    && echo "LLVM_CC_NAME=clang-6.0" >> /benchmarks/configs/env \
    && echo "LLVM_CXX_NAME=clang-6.0" >> /benchmarks/configs/env \
    && echo "WLLVM_DIR=/usr/local/bin" >> /benchmarks/configs/env \
    && echo "SULONG_DIR=/graalvm/graal/sulong" >> /benchmarks/configs/env

ENTRYPOINT ["/benchmarks/tools/bench.py", "/data/sulong.json", "--no-papi"] FOREGROUND
