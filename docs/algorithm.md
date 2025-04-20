# Algorithm Summary and Parallelization Plan

## 1. Serial Butterfly‑Counting Pseudocode

From Algorithms 2–4 (GET‑WEDGES + COUNT‑V‑WEDGES):

```text
// Assume G = (V, E) is preprocessed (vertices renamed by rank, neighbors sorted)
procedure COUNT_BUTTERFLIES_PER_VERTEX(G):
  // Step 1: Enumerate all wedges (u1→v→u2) in parallel
  W ← []  // array of (u1, u2, center = v)
  parfor u1 ∈ V:
    for each neighbor v of u1:
      for each neighbor u2 of v:
        if rank(u2) > rank(u1) and rank(v) > rank(u1):
          append (u1, u2, v) to W

  // Step 2: Group by endpoints and count frequencies
  // GET-FREQ returns:
  //   R = [ ((u1,u2), freq)  ... ]
  //   F = [ start indices in W for each group ]
  (R, F) ← GET_FREQ(W)

  // Step 3: For each ((u1,u2), d) in R:
  //    • Each endpoint u1 and u2 sees d choose 2 butterflies
  //    • Each wedge center v contributes (d−1) butterflies
  B ← []  // (entity, count) pairs
  parfor i in 0..|R|−1:
    ((u1,u2), d) ← R[i]
    B.append((u1, C(d,2)))
    B.append((u2, C(d,2)))
    for j in F[i] .. F[i+1]−1:
      ( , , v) ← W[j]
      B.append((v, d−1))

  // Step 4: Aggregate B by key to get final per-vertex counts
  (Counts, _) ← GET_FREQ(B)
  return Counts