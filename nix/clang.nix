{ vanillaNixpkgs }:
final: prev:
rec {
  inherit (vanillaNixpkgs)
    bison
    boost-build
    cmake
    expect
    libxslt
    libxml2
    ninja
    openssl
    python3;
  llvm = prev.llvm_16;
  llvmPackages = prev.llvmPackages_16;
  clangStdenv = llvmPackages.libcxxStdenv;
  clang-tools = prev.clang-tools.override { inherit llvmPackages; };
  lldb = llvmPackages.lldb;
}
