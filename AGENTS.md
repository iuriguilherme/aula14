# AGENTS.md

This file provides guidance to agents when working with code in this repository.

## Build/Test Commands
- `make test`: Runs all unit tests via [`test_runner.c`](tests/test_runner.c) (no single test support)
- `make debug`: Compiles with `-DVERBOSE` for detailed logging (use `#ifdef VERBOSE`)
- No linter configured (pure C11, no clang-format/eslint)

## Critical Patterns
- Dynamic arrays: Use [`PontoArray`](include/structs.h) with [`realocar_ponto_array`](include/pontos.h) - always check realloc return
- Interpolation: [`lagrange_interpolation`](src/lagrange.c) assumes distinct x values (div0 risk on duplicates)
- Generator: [`gerar_pontos`](src/generator.c) creates unsorted points; sort via [`bubble_sort_ponto`](src/ordering.c) if needed
- JSON export: Always to `interpolacao.json` for [`visualizar.html`](visualizar.html)
- MAX_POINTS=300 in [`local_config.h`](include/local_config.h)

## Code Style
- Debug: `#ifdef VERBOSE` throughout (not DEBUG)
- Memory: Manual free after PontoArray use
- No auto-sorting; tests verify bubble_sort/reverse manually