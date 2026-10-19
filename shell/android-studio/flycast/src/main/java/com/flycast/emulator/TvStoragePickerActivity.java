package com.flycast.emulator;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.net.Uri;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

/**
 * Small remote-control-friendly fallback for Android TV devices that do not
 * provide a system Storage Access Framework picker.
 *
 * The selected location is returned as a file:// URI. Access is still subject
 * to the Android version, storage permissions, and the device's USB mount policy.
 */
public final class TvStoragePickerActivity extends Activity {
    public static final String EXTRA_DIRECTORY = "recast.pick.directory";
    public static final String EXTRA_DESCRIPTION = "recast.pick.description";
    public static final String EXTRA_MIME_TYPE = "recast.pick.mime";
    private static final String PARENT_ROW = "⬅  ..";

    private boolean directoryMode;
    private File currentDirectory;
    private TextView locationLabel;
    private TextView statusLabel;
    private ListView listView;
    private Button chooseButton;
    private Button rootsButton;
    private ArrayAdapter<String> adapter;
    private final List<File> visibleFiles = new ArrayList<>();
    private final List<String> visibleLabels = new ArrayList<>();
    private boolean showingRoots;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        directoryMode = getIntent().getBooleanExtra(EXTRA_DIRECTORY, true);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        buildUi();
        showRoots();
    }

    private void buildUi() {
        LinearLayout root = new LinearLayout(this);
        root.setOrientation(LinearLayout.VERTICAL);
        root.setPadding(dp(24), dp(18), dp(24), dp(18));
        root.setBackgroundColor(0xFF171923);

        TextView title = new TextView(this);
        title.setText("RECAST  •  Seleccionar " + (directoryMode ? "carpeta" : "archivo"));
        title.setTextColor(0xFFFFD2F0);
        title.setTextSize(22);
        title.setPadding(0, 0, 0, dp(10));
        root.addView(title, new LinearLayout.LayoutParams(-1, -2));

        locationLabel = new TextView(this);
        locationLabel.setTextColor(0xFFE7EAF4);
        locationLabel.setTextSize(15);
        locationLabel.setPadding(0, dp(4), 0, dp(8));
        root.addView(locationLabel, new LinearLayout.LayoutParams(-1, -2));

        listView = new ListView(this);
        listView.setChoiceMode(ListView.CHOICE_MODE_SINGLE);
        adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, visibleLabels) {
            @Override
            public View getView(int position, View convertView, android.view.ViewGroup parent) {
                TextView view = (TextView) super.getView(position, convertView, parent);
                view.setTextColor(0xFFFFFFFF);
                view.setTextSize(18);
                view.setPadding(dp(12), dp(10), dp(12), dp(10));
                view.setBackgroundColor(position % 2 == 0 ? 0xFF242938 : 0xFF1D2230);
                return view;
            }
        };
        listView.setAdapter(adapter);
        root.addView(listView, new LinearLayout.LayoutParams(-1, 0, 1));

        statusLabel = new TextView(this);
        statusLabel.setTextColor(0xFFFFD2F0);
        statusLabel.setTextSize(13);
        statusLabel.setPadding(0, dp(8), 0, dp(6));
        root.addView(statusLabel, new LinearLayout.LayoutParams(-1, -2));

        LinearLayout buttons = new LinearLayout(this);
        buttons.setOrientation(LinearLayout.HORIZONTAL);
        buttons.setGravity(Gravity.CENTER_VERTICAL);
        rootsButton = new Button(this);
        rootsButton.setText("Almacenamientos");
        rootsButton.setOnClickListener(v -> showRoots());
        buttons.addView(rootsButton, new LinearLayout.LayoutParams(0, -2, 1));

        chooseButton = new Button(this);
        chooseButton.setText(directoryMode ? "Usar esta carpeta" : "Seleccionar archivo");
        chooseButton.setOnClickListener(v -> chooseCurrentDirectory());
        buttons.addView(chooseButton, new LinearLayout.LayoutParams(0, -2, 1));
        root.addView(buttons, new LinearLayout.LayoutParams(-1, -2));

        setContentView(root);
        listView.setOnItemClickListener((parent, view, position, id) -> onRowSelected(position));
        listView.setOnItemLongClickListener((parent, view, position, id) -> {
            File file = position < visibleFiles.size() ? visibleFiles.get(position) : null;
            if (!showingRoots && file != null && file.isFile() && !directoryMode) {
                finishWith(file);
                return true;
            }
            return false;
        });
    }

    private void showRoots() {
        showingRoots = true;
        currentDirectory = null;
        visibleFiles.clear();
        visibleLabels.clear();
        Set<File> roots = new LinkedHashSet<>();
        File internal = Environment.getExternalStorageDirectory();
        if (internal != null && internal.exists() && internal.canRead())
            roots.add(internal);

        File storage = new File("/storage");
        File[] mounts = storage.listFiles();
        if (mounts != null) {
            for (File mount : mounts) {
                String name = mount.getName();
                if ("emulated".equals(name) || "self".equals(name)) {
                    if ("emulated".equals(name)) {
                        File primary = new File(mount, "0");
                        if (primary.exists() && primary.canRead()) roots.add(primary);
                    }
                    continue;
                }
                if (mount.isDirectory() && mount.canRead())
                    roots.add(mount);
            }
        }
        for (String mount : FileBrowser.getExternalMounts()) {
            File file = new File(mount);
            if (file.isDirectory() && file.canRead()) roots.add(file);
        }

        List<File> sorted = new ArrayList<>(roots);
        Collections.sort(sorted, Comparator.comparing(File::getAbsolutePath, String.CASE_INSENSITIVE_ORDER));
        for (File dir : sorted) {
            visibleFiles.add(dir);
            String label = dir.getAbsolutePath();
            if (label.equals(internal.getAbsolutePath())) label += "  (Interno)";
            else if (label.startsWith("/storage/") && !label.contains("/emulated/")) label += "  (USB / SD)";
            visibleLabels.add("📁  " + label);
        }
        locationLabel.setText("Elige una unidad");
        statusLabel.setText(sorted.isEmpty()
                ? "No se detectaron unidades accesibles. Comprueba los permisos de almacenamiento."
                : "Unidades detectadas: " + sorted.size() + ". Usa las flechas y OK.");
        chooseButton.setEnabled(false);
        adapter.notifyDataSetChanged();
        listView.requestFocus();
    }

    private void openDirectory(File directory) {
        if (directory == null || !directory.isDirectory() || !directory.canRead()) {
            statusLabel.setText("No se puede leer esta carpeta con los permisos actuales.");
            return;
        }
        showingRoots = false;
        currentDirectory = directory;
        visibleFiles.clear();
        visibleLabels.clear();
        File parent = directory.getParentFile();
        if (parent != null) {
            visibleFiles.add(parent);
            visibleLabels.add(PARENT_ROW);
        }
        File[] children = directory.listFiles();
        if (children != null) {
            List<File> dirs = new ArrayList<>();
            List<File> files = new ArrayList<>();
            for (File child : children) {
                if (child.isDirectory()) dirs.add(child);
                else if (!directoryMode && child.isFile()) files.add(child);
            }
            Comparator<File> byName = Comparator.comparing(File::getName, String.CASE_INSENSITIVE_ORDER);
            Collections.sort(dirs, byName);
            Collections.sort(files, byName);
            for (File dir : dirs) {
                visibleFiles.add(dir);
                visibleLabels.add("📁  " + dir.getName() + "/");
            }
            for (File file : files) {
                visibleFiles.add(file);
                visibleLabels.add("📄  " + file.getName());
            }
        }
        locationLabel.setText(directory.getAbsolutePath());
        statusLabel.setText(directoryMode
                ? "Entra a una carpeta o elige la carpeta actual."
                : "Selecciona un archivo compatible con Recast.");
        chooseButton.setEnabled(directoryMode);
        adapter.notifyDataSetChanged();
        listView.setSelection(0);
        listView.requestFocus();
    }

    private void onRowSelected(int position) {
        if (position < 0 || position >= visibleFiles.size()) return;
        File file = visibleFiles.get(position);
        if (showingRoots || file.isDirectory()) {
            openDirectory(file);
        } else if (!directoryMode && file.isFile()) {
            finishWith(file);
        }
    }

    private void chooseCurrentDirectory() {
        if (directoryMode && currentDirectory != null)
            finishWith(currentDirectory);
    }

    private void finishWith(File file) {
        if (file == null || !file.exists()) {
            setResult(Activity.RESULT_CANCELED);
            finish();
            return;
        }
        android.content.Intent result = new android.content.Intent();
        result.setData(Uri.fromFile(file));
        setResult(Activity.RESULT_OK, result);
        finish();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {
            if (!showingRoots && currentDirectory != null) {
                File parent = currentDirectory.getParentFile();
                if (parent != null) openDirectory(parent);
                else showRoots();
                return true;
            }
            if (!showingRoots) {
                showRoots();
                return true;
            }
        }
        return super.onKeyDown(keyCode, event);
    }

    private int dp(int value) {
        return (int) (value * getResources().getDisplayMetrics().density + 0.5f);
    }
}
