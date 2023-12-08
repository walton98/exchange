{ vanillaNixpkgs }:
final: prev:
rec {
  inherit (vanillaNixpkgs)
    bison
    boost-build
    cmake
    expect
    libffi
    libxslt
    libxml2
    ninja
    openssl
    python3;
  llvm = prev.llvm_17;
  llvmPackages = prev.llvmPackages_17;
  clangStdenv = llvmPackages.libcxxStdenv;
  clang-tools = prev.clang-tools.override { inherit llvmPackages; };
  lldb = llvmPackages.lldb;
  catch2_3 = prev.catch2_3.overrideAttrs(old: {
    NIX_CFLAGS_COMPILE = [
      "-Wno-deprecated-literal-operator"
    ];
  });
}
