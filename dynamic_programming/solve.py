import graphviz

# Global setup for the Graphviz tree
dot = graphviz.Digraph(comment="Complete Recursion Tree")
dot.attr(rankdir="TB")  # Top to Bottom
dot.attr("node", shape="box", style="rounded,filled", fontname="Helvetica")

call_counter = 0


def solve_visualized(b, i, T, parts, memo, parent_id=None):
    global call_counter

    # 1. Assign a globally unique ID to this specific invocation
    call_counter += 1
    current_id = str(call_counter)

    result = None
    node_color = "lightblue"  # Default color for standard computation

    # --- 2. Your Confirmed Logic ---
    if b < 0:
        result = -1
        node_color = "#ff9999"  # Light Red for invalid base case

    elif i == T + 1:
        result = 0
        node_color = "#99ff99"  # Light Green for valid base case

    elif (b, i) in memo and memo[(b, i)] > 0:
        result = memo[(b, i)]
        node_color = "#ffff99"  # Light Yellow for Memoization hits

    else:
        best_val = -1
        for cost, val in parts.get(i, []):
            # Pass current_id down so children know who called them
            ret = solve_visualized(b - cost, i + 1, T, parts, memo, current_id)

            if ret < 0:
                continue

            if (ret + val) > best_val:
                best_val = ret + val

        if best_val > 0:
            memo[(b, i)] = best_val

        result = best_val

    # --- 3. Draw the Node and Edge ---
    # We do this AFTER the logic so we can include the final 'result' in the label
    label = f"solve(b={b}, i={i})\n➔ {result}"
    dot.node(current_id, label, fillcolor=node_color)

    # If this call was spawned by another call, connect them
    if parent_id is not None:
        dot.edge(parent_id, current_id)

    return result


def main():
    # Your exact CCO '10 P4 sample input
    input_data = """2
5
10 6 1
5 7 1
6 10 2
1 5 1
11 11 2
16"""

    tokens = iter(input_data.split())

    def next_int():
        return int(next(tokens))

    T = next_int()
    n = next_int()

    parts = {}
    for _ in range(n):
        c = next_int()
        v = next_int()
        t = next_int()

        if t not in parts:
            parts[t] = []

        # Inserting at 0 ensures the traversal matches your C logic exactly
        parts[t].insert(0, (c, v))

    B = next_int()
    memo = {}

    print("Running visualized solve...")
    final_result = solve_visualized(B, 1, T, parts, memo)
    print(f"Final Answer: {final_result}")

    # Render and open the image
    output_filename = "complete_recursion_tree"
    print(f"Generating diagram: {output_filename}.png")
    dot.render(output_filename, format="png", view=True, cleanup=True)


if __name__ == "__main__":
    main()
