{
  description = "Exchange project.";

  inputs.nixpkgs.url = "github:nixos/nixpkgs";
  inputs.flake-utils.url = "github:numtide/flake-utils";


  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        vanillaNixpkgs = import nixpkgs {
          inherit system;
        };

        clangOverlay = (import ./nix/clang.nix){
          inherit vanillaNixpkgs;
        };

        clangPkgs = import nixpkgs {
          inherit system;
          config = {
            replaceStdenv = { pkgs }: pkgs.clangStdenv;
          };
          overlays = [
            (import ./nix/protobuf.nix)
            clangOverlay
          ];
        };

        python3 = clangPkgs.python3.withPackages (p: with p; [
          protobuf
          pytest
        ]);

        shell = clangPkgs.mkShell rec {
          name = "exchange";
          shellHook = ''
            generate_protos() {
              protoc --proto_path=packages/protos/defs --cpp_out=packages/protos/src packages/protos/defs/*.proto
            }

            generate_test_protos() {
              protoc --proto_path=packages/protos/defs --python_out=matcher/test packages/protos/defs/*.proto
            }

            link_compile_commands() {
              rm compile_commands.json
              ln -s `pwd`/build/compile_commands.json `pwd`/compile_commands.json
            }
          '';
          # Prioritise clang-tools in PATH so that we use clangd from
          # clang-tools. See https://github.com/NixOS/nixpkgs/pull/203434
          nativeBuildInputs = [ clangPkgs.clang-tools ];
          buildInputs = with clangPkgs; [
            # C++ libraries
            asio
            boost
            protobuf3_21
            spdlog

            # Build tools
            cmake
            ninja
            # TODO: fix lldb build
            # lldb

            # Linting
            cppcheck
            # include-what-you-use

            # Testing
            catch2_3

            entr
          ] ++ [
            # Test client
            python3
          ];
        };
      in {
        devShells.default = shell;
        # TODO: make an actual package to build project
        packages.default = shell;
      }
    );
}
